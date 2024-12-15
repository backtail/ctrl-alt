#include "k_timer_calc.h"

// @brief Calculates the prescaler and counter value based on the CPU frequency and desired timer update frequency.
// @param cpu_frequency The CPU frequency in Hz
// @param desired_frequency The desired timer update frequency in Hz
// @return `tim_config_t` struct with calculated prescaler bit shift and counter values
void get_tim_config_prescaler_bit_shifted(uint32_t cpu_frequency, float desired_frequency, uint32_t max_prescaler_bit_shift, uint32_t max_counter_val, tim_config_t *c)
{
    // configure to slowest possible as default
    // tim_config_t c = {.prescaler = max_prescaler_bit_shift, .counter = max_counter_val};

    // if frequency either
    //  - is too low to achieve
    //  - equal to 0
    //  - higher than CPU frequency
    c->prescaler = max_prescaler_bit_shift;
    c->counter = max_counter_val;

    if (desired_frequency >= 0.0f && desired_frequency < cpu_frequency)
    {
        // Iterate over possible prescaler values (0 to 15)
        for (uint8_t presc = 0; presc <= max_prescaler_bit_shift; ++presc)
        {
            uint32_t division_factor = 1U << presc; // Calculate 2^prescaler

            // Calculate the base frequency after prescaler
            float base_frequency = (float)cpu_frequency / division_factor;

            // Calculate the counter value (rounding appropriately)
            float cnt = base_frequency / desired_frequency;

            // Check if the counter value is valid (1 to 65535)
            if (cnt > 1 && cnt <= max_counter_val)
            {
                c->prescaler = (uint8_t)presc;
                c->counter = (uint16_t)cnt;
                break; // leave loop (and also function)
            }
        }
    }
}