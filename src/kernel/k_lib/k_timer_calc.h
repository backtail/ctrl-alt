#ifndef _K_TIMER_CALC_H_
#define _K_TIMER_CALC_H_

#include "stdint.h"

// abstract struct that does not concern with architecture of underlying HW
typedef struct TIM_CONFIG
{
    uint16_t prescaler;
    uint16_t counter;
} tim_config_t;

void get_tim_config_prescaler_bit_shifted(uint32_t cpu_frequency, float desired_frequency, uint32_t max_prescaler_bit_shift, uint32_t max_counter_val, tim_config_t *c);

#endif // _K_TIMER_CALC_H_
