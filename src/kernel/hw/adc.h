#ifndef _K_HW_ADC_
#define _K_HW_ADC_

/// @brief Inits all necessary peripherals and its configurations
void setup_adc(void);

/// @brief Starts all necessary peripherals, after interrupts have been enabled
void start_adc(void);

/// @brief Handles the ADC hardware in the main loop
void handle_adc(void);

#endif //_K_HW_ADC_