#include "user_program.h"

#ifdef MASTER_CLK

#include "kernel/interrupts.h"

#include "kernel/api/gpio.h"
#include "kernel/api/adc.h"
#include "kernel/api/dac.h"

// should probably unify this in an API
#include "kernel/k_lib/k_timer_calc.h"
#include "stm8s_tim3.h"

#include "lerp_lut.h"
#include "math.h"

#define SYSTICK 100 // us
#define LUT_SIZE 64
#define LUT_MAX_VAL (1023)

uint16_t time_log_lut[LUT_SIZE] = {0};

uint32_t systick_counter = 0;

bool master_clk_state = 1;
uint32_t master_clk_edge = 10000;

bool mult_clk_state = 1;
uint32_t mult_clk_edge = 10000;

void update_clocks()
{
    uint16_t time = interpolate_lut(1023 - get_adc(POT0), time_log_lut, LUT_MAX_VAL, LUT_SIZE);
    master_clk_edge = 1024 + (time << 3);
    if (master_clk_state == mult_clk_state)
        mult_clk_edge = master_clk_edge >> (get_adc(POT1) >> 8);
}

void exti_it_callback() {}

void tim3_it_callback()
{
    TIM3_ClearITPendingBit(TIM3_IT_UPDATE);

    static uint32_t last_master_clk_edge;
    static uint32_t last_mult_clk_edge;

    if (systick_counter - last_mult_clk_edge >= mult_clk_edge)
    {
        last_mult_clk_edge = systick_counter; // update

        set_pin(&OUT1, mult_clk_state);
        mult_clk_state ^= 1;
    }

    if (systick_counter - last_master_clk_edge >= master_clk_edge)
    {
        last_master_clk_edge = systick_counter; // update

        if (mult_clk_state)
            last_mult_clk_edge = systick_counter; // sync multiplier

        set_pin(&OUT0, master_clk_state);
        master_clk_state ^= 1;

        update_clocks();
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
}

void start()
{
    TIM3_Cmd(ENABLE);
}

void update() {}

#endif // WAVETABLE_LFO