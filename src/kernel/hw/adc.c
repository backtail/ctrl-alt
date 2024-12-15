////////////////////////////////////////////////////////////////////////////////
// ADC API IMPLEMENTAION
////////////////////////////////////////////////////////////////////////////////

#include "kernel/api/adc.h"

#define N_ADC_CH 6

uint16_t raw_adc_vals[N_ADC_CH] = {0};

uint16_t get_adc(adc_channel_t ch)
{
    return raw_adc_vals[(uint8_t)ch];
}

////////////////////////////////////////////////////////////////////////////////
// ADC KERNEL IMPLEMENTAION
////////////////////////////////////////////////////////////////////////////////

#include "kernel/hw/adc.h"

#include "stm8s_adc1.h"

#include "hw_config.h"
#include "kernel/interrupts.h"
#include "kernel/k_lib/k_timer_calc.h"

// these function pointers are only used by the kernel
extern void (*it_adc_handler)(void);
extern void (*it_tim2_upd_ovf_brk_handler)(void);

////////////////////////////////////////////////////////////////////////////////
// PRIVATE

// optimised implementation of SPL driver for the case of right alignment
inline void adc_get_right_aligned(adc_channel_t ch, uint16_t *buf)
{
    buf[(uint8_t)ch] = *(uint16_t *)(uint16_t)((uint16_t)ADC1_BaseAddress + (uint8_t)(ch << 1));
}

// TIM2 triggers the ADC conversion at a rate of `ADC_SAMPLE_RATE`
void tim2_it_update_callback(void)
{
    TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
    ADC1_StartConversion(); // restart ADC conversion
}

// store converted ADC values and wait for TIM2 to wrap around
void adc_eoc_callback(void)
{
    ADC1_ClearITPendingBit(ADC1_IT_EOC);

    adc_get_right_aligned(POT0, raw_adc_vals);
    adc_get_right_aligned(POT1, raw_adc_vals);
    adc_get_right_aligned(POT2, raw_adc_vals);
    adc_get_right_aligned(CV0, raw_adc_vals);
    adc_get_right_aligned(CV1, raw_adc_vals);
    adc_get_right_aligned(CV2, raw_adc_vals);
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC

/// @brief Inits all necessary peripherals and its configurations
void setup_adc(void)
{
    // setup ADC config
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
              ADC1_CHANNEL_5,
              ADC1_PRESSEL_FCPU_D2,
              ADC1_EXTTRIG_TIM, DISABLE,
              ADC1_ALIGN_RIGHT,
              ADC1_SCHMITTTRIG_CHANNEL0, DISABLE);

    ADC1_ITConfig(ADC1_IT_EOCIE, ENABLE);
    ADC1_DataBufferCmd(ENABLE);
    ADC1_ScanModeCmd(ENABLE);
    ADC1_Cmd(ENABLE);

    tim_config_t conf;
    get_tim_config_prescaler_bit_shifted(CPU_FREQ, ADC_SAMPLE_RATE, MAX_PRESCALER_DIVISOR, MAX_COUNTER_VALUE, &conf);

    // make the ADC restart conversion based on this timer
    TIM2_TimeBaseInit((uint8_t)conf.prescaler, (uint16_t)conf.counter);
    TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);

    // assign interrupt function pointers
    it_adc_handler = adc_eoc_callback;
    it_tim2_upd_ovf_brk_handler = tim2_it_update_callback;
}

/// @brief Starts all necessary peripherals, after interrupts have been enabled
void start_adc(void)
{
    TIM2_Cmd(ENABLE);
    ADC1_StartConversion();
}
