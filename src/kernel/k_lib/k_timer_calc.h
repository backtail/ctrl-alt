#ifndef _K_TIMER_CALC_H_
#define _K_TIMER_CALC_H_

#include "stdint.h"

/// @brief Defines hardware configuration for a timer
/// @details Abstract struct that does not concern with architecture of underlying HW
typedef struct TIM_CONFIG
{
    uint16_t prescaler; ///< Prescaler value (0-15)
    uint16_t counter;   ///< Counter value (1-65535)
} tim_config_t;

/// @brief Calculates the prescaler and counter value based on the CPU frequency and desired timer update frequency.
/// @param cpu_frequency The CPU frequency in Hz
/// @param desired_frequency The desired timer update frequency in Hz
/// @param max_prescaler_bit_shift The maximum prescaler bit shift value (0-15)
/// @param max_counter_val The maximum counter value (1-65535)
/// @param c Pointer to a `tim_config_t` struct to store the calculated prescaler and counter values
/// @return `tim_config_t` struct with calculated prescaler bit shift and counter values
void get_tim_config_prescaler_bit_shifted(uint32_t cpu_frequency, float desired_frequency, uint32_t max_prescaler_bit_shift, uint32_t max_counter_val, tim_config_t *c);

#endif // _K_TIMER_CALC_H_
