#include "kernel/api/dac.h"
#include "kernel/hw/dac.h"

#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)

#include "stm8s_tim1.h"
#include "stm8s_tim3.h"

#include "kernel/interrupts.h"
#include "kernel/k_lib/k_timer_calc.h"

// make sure that dac latency is always defined
#ifndef DAC_LATENCY
#define DAC_LATENCY 1
#endif

#if DAC_LATENCY > 1
#include "kernel/k_lib/k_ring_buffer.h"
#endif

bool dac_update_flag = 0; // indicates if new dac values need to calculated
void (*dac_callback)(void) = NULL_POINTER;

#if OUTPUT0 == ANALOG_OUT
#if DAC_LATENCY > 1
RingBuffer dac0_rb = {0};
#endif
uint8_t dac0_latency_buffer[DAC_LATENCY] = {0}; // holds the ring buffer data
#endif

#if OUTPUT1 == ANALOG_OUT
#if DAC_LATENCY > 1
RingBuffer dac1_rb = {0};
#endif
uint8_t dac1_latency_buffer[DAC_LATENCY] = {0}; // holds the ring buffer data
#endif

#if OUTPUT2 == ANALOG_OUT
#if DAC_LATENCY > 1
RingBuffer dac2_rb = {0};
#endif
uint8_t dac2_latency_buffer[DAC_LATENCY] = {0}; // holds the ring buffer data
#endif

void tim3_update_it_callback(void)
{
    TIM3_ClearITPendingBit(TIM3_IT_UPDATE);

#if OUTPUT0 == ANALOG_OUT
#if DAC_LATENCY > 1
    TIM1_SetCompare1(ring_buffer_get(&dac0_rb));
#else
    TIM1_SetCompare1(dac0_latency_buffer[0]);
#endif
#endif

#if OUTPUT1 == ANALOG_OUT
#if DAC_LATENCY > 1
    TIM1_SetCompare2(ring_buffer_get(&dac1_rb));
#else
    TIM1_SetCompare2(dac1_latency_buffer[0]);
#endif
#endif

#if OUTPUT2 == ANALOG_OUT
#if DAC_LATENCY > 1
    TIM1_SetCompare3(ring_buffer_get(&dac2_rb));
#else
    TIM1_SetCompare3(dac2_latency_buffer[0]);
#endif
#endif

#if DAC_LATENCY > 1
    static uint16_t c;

    c++;

    if (c >= DAC_LATENCY)
    {
        dac_update_flag = 1;
        c = 0;
    }
#else
    dac_update_flag = 1;
#endif
}

void setup_dac()
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3, ENABLE);

    TIM1_TimeBaseInit(0,                   // prescaler
                      TIM1_COUNTERMODE_UP, // count up
                      1 << 8,              // period
                      1);                  // reps (ignored)

    TIM1_ARRPreloadConfig(ENABLE);

    tim_config_t conf;
    get_tim_config_prescaler_bit_shifted(CPU_FREQ, DAC_SAMPLE_RATE, MAX_PRESCALER_DIVISOR, MAX_COUNTER_VALUE, &conf);

    // make the PWM DAC restart conversion based on this timer
    TIM3_TimeBaseInit((uint8_t)conf.prescaler, (uint16_t)conf.counter);
    TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE); // configure interrupt

#if OUTPUT0 == ANALOG_OUT
    GPIOC->CR1 = GPIO_PIN_1; // GPIO AF

    TIM1_OC1Init(TIM1_OCMODE_PWM1,
                 TIM1_OUTPUTSTATE_ENABLE,
                 TIM1_OUTPUTNSTATE_DISABLE,
                 1 << 7, // set to 50%
                 TIM1_OCPOLARITY_HIGH,
                 TIM1_OCNPOLARITY_LOW,
                 TIM1_OCIDLESTATE_RESET,
                 TIM1_OCNIDLESTATE_RESET);

#endif

#if OUTPUT1 == ANALOG_OUT
    GPIOC->CR1 = GPIO_PIN_2; // GPIO AF

    TIM1_OC2Init(TIM1_OCMODE_PWM1,
                 TIM1_OUTPUTSTATE_ENABLE,
                 TIM1_OUTPUTNSTATE_DISABLE,
                 1 << 7, // set to 50%
                 TIM1_OCPOLARITY_HIGH,
                 TIM1_OCNPOLARITY_LOW,
                 TIM1_OCIDLESTATE_RESET,
                 TIM1_OCNIDLESTATE_RESET);
#endif

#if OUTPUT2 == ANALOG_OUT
    GPIOC->CR1 = GPIO_PIN_3; // GPIO AF

    TIM1_OC3Init(TIM1_OCMODE_PWM1,
                 TIM1_OUTPUTSTATE_ENABLE,
                 TIM1_OUTPUTNSTATE_DISABLE,
                 1 << 7, // set to 50%
                 TIM1_OCPOLARITY_HIGH,
                 TIM1_OCNPOLARITY_LOW,
                 TIM1_OCIDLESTATE_RESET,
                 TIM1_OCNIDLESTATE_RESET);
#endif

    it_tim3_upd_ovf_brk_handler = tim3_update_it_callback; // hook interrupt handler

#if DAC_LATENCY > 1

#if OUTPUT0 == ANALOG_OUT
    ring_buffer_init(&dac0_rb, dac0_latency_buffer, DAC_LATENCY);
#endif

#if OUTPUT1 == ANALOG_OUT
    ring_buffer_init(&dac1_rb, dac1_latency_buffer, DAC_LATENCY);
#endif

#if OUTPUT2 == ANALOG_OUT
    ring_buffer_init(&dac2_rb, dac2_latency_buffer, DAC_LATENCY);
#endif

#endif // DAC LATENCY > 1
}

void start_dac()
{
    TIM1_CtrlPWMOutputs(ENABLE);
    TIM1_Cmd(ENABLE);
    TIM3_Cmd(ENABLE);
}

void handle_dac()
{
    if (dac_update_flag)
    {
        dac_update_flag = 0;

        dac_callback();
    }
}

#if OUTPUT0 == ANALOG_OUT
void set_dac0(uint8_t val)
{
#if DAC_LATENCY > 1
    ring_buffer_put(&dac0_rb, val);
#else
    dac0_latency_buffer[0] = val;
#endif
}
#endif

#if OUTPUT1 == ANALOG_OUT
void set_dac1(uint8_t val)
{
#if DAC_LATENCY > 1
    ring_buffer_put(&dac1_rb, val);
#else
    dac1_latency_buffer[0] = val;
#endif
}
#endif

#if OUTPUT2 == ANALOG_OUT
void set_dac2(uint8_t val)
{
#if DAC_LATENCY > 1
    ring_buffer_put(&dac2_rb, val);
#else
    dac2_latency_buffer[0] = val;
#endif
}
#endif

#endif