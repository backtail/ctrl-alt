#include "user_program.h"

#include "kernel/interrupts.h"

#include "kernel/api/gpio.h"
#include "kernel/api/adc.h"
#include "kernel/api/dac.h"

// should probably unify this in an API
#include "kernel/k_lib/k_timer_calc.h"
#include "stm8s_tim3.h"

#include "clamp.h"
#include "lerp_lut.h"
#include "lerp.h"
#include "math.h"

#define SYSTICK 100 // us
#define LUT_SIZE 512
#define LUT_MAX_VAL (1023)

uint16_t time_log_lut[LUT_SIZE] = {0};

bool mult_1_clk_state = 1;
bool mult_2_clk_state = 1;
bool master_clk_state = 1;
uint32_t master_full_cycle = 100;

uint8_t mult_1 = 0;
uint8_t mult_2 = 0;

uint8_t master_shift = 0;
uint8_t mult_1_shift = 0;
uint8_t mult_2_shift = 0;

uint32_t lerp(uint32_t a, uint32_t b, uint16_t weight)
{
    uint16_t complement_weight = 1023 - weight;

    // Compute weighted contributions
    uint32_t contrib1 = (uint32_t)complement_weight * a;
    uint32_t contrib2 = (uint32_t)weight * b;

    // Combine and normalize
    return ((contrib1 + contrib2) >> 10);
}

void update_clocks()
{
    // uint16_t param0 = clamp_10_bit(1023 - get_adc(POT0) + 1023 - get_adc(CV0));
    uint16_t pot0 = 1023 - get_adc(POT0);
    uint16_t cv0 = get_adc(CV0);
    uint16_t param0 = clamp_10_bit(pot0 + cv0);
    uint16_t master_time = time_log_lut[param0 >> 1]; // log LUT conversion
    master_full_cycle = 100 + (master_time << 2);

    mult_1 = clamp_10_bit(get_adc(POT1) + get_adc(CV1)) >> 8;
    mult_2 = clamp_10_bit(get_adc(POT2) + get_adc(CV2)) >> 8;
}

void exti_it_callback()
{
    if (read_pin(&IN0))
    {
        master_shift++;
        set_pin(&LED0, HIGH);
    }

    if (read_pin(&IN1))
    {
        mult_1_shift++;
        set_pin(&LED1, HIGH);
    }

    if (read_pin(&IN2))
    {
        mult_2_shift++;
        set_pin(&LED2, HIGH);
    }

    if (read_pin(&TRIGGER_SWITCH))
    {
        master_shift = 0;
        mult_1_shift = 0;
        mult_2_shift = 0;

        set_pin(&LED0, HIGH);
        set_pin(&LED1, HIGH);
        set_pin(&LED2, HIGH);
    }
}

void tim3_it_callback()
{
    TIM3_ClearITPendingBit(TIM3_IT_UPDATE);

    static uint32_t systick_counter; // ticks @100us
    static uint32_t last_systick;    // timestamp of last systick occurence

    static uint32_t master_clk_rising; // time at which resp. clock signal rose
    static uint32_t mult_1_clk_rising; // time at which resp. clock signal rose
    static uint32_t mult_2_clk_rising; // time at which resp. clock signal rose

    if (systick_counter - last_systick >= master_full_cycle)
    {
        static uint8_t edge_counter;

        last_systick = systick_counter; // update

        update_clocks();

        set_pin(&LED0, LOW);
        set_pin(&LED1, LOW);
        set_pin(&LED2, LOW);

        // master clock oversampled with 16 internal clock ticks
        if (((edge_counter + master_shift) & 0b1000) && master_clk_state == LOW)
        {
            set_pin(&OUT0, HIGH);
            master_clk_state = HIGH;
            master_clk_rising = systick_counter;
        }

        // oversampling can be minimzed by mult_1, resulting in a faster clk
        if (((edge_counter + mult_1_shift) & (0b1000 >> mult_1)) && mult_1_clk_state == LOW)
        {
            set_pin(&OUT1, HIGH);
            mult_1_clk_state = HIGH;
            mult_1_clk_rising = systick_counter;
        }

        // oversampling can be minimzed by mult_2, resulting in a faster clk
        if (((edge_counter + mult_2_shift) & (0b1000 >> mult_2)) && mult_2_clk_state == LOW)
        {
            set_pin(&OUT2, HIGH);
            mult_2_clk_state = HIGH;
            mult_2_clk_rising = systick_counter;
        }

        edge_counter++;
        if (edge_counter >= (1 << 4))
        {
            edge_counter = 0;
        }
    }

    if ((systick_counter - master_clk_rising >= master_full_cycle << 3) && master_clk_state == HIGH)
    {
        set_pin(&OUT0, LOW);
        master_clk_state = LOW;
    }

    if ((systick_counter - mult_1_clk_rising >= (master_full_cycle << 3) >> mult_1) && mult_1_clk_state == HIGH)
    {
        set_pin(&OUT1, LOW);
        mult_1_clk_state = LOW;
    }

    if ((systick_counter - mult_2_clk_rising >= (master_full_cycle << 3) >> mult_2) && mult_2_clk_state == HIGH)
    {
        set_pin(&OUT2, LOW);
        mult_2_clk_state = LOW;
    }

    systick_counter++;
}

void setup()
{
    tim_config_t conf;
    get_tim_config_prescaler_bit_shifted(CPU_FREQ, 1000000.0f / SYSTICK, MAX_PRESCALER_DIVISOR, MAX_COUNTER_VALUE, &conf);

    // make the PWM DAC restart conversion based on this timer
    TIM3_TimeBaseInit((uint8_t)conf.prescaler, (uint16_t)conf.counter);
    TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE); // configure interrupt

    for (int i = 1; i < LUT_SIZE; i++)
    {
        time_log_lut[i] = (uint16_t)(powf((float)i / (LUT_SIZE - 1), 3.0f) * LUT_MAX_VAL);
    }

    // assign interrupt callbacks
    it_tim3_upd_ovf_brk_handler = tim3_it_callback;
    it_exti_portd_handler = exti_it_callback;
}

void start()
{
    TIM3_Cmd(ENABLE);
}

void update() {}