#ifndef _K_API_ADC_
#define _K_API_ADC_

#include "stdint.h"

/// @brief ADC channel enumeration
typedef enum adc_channel
{
    POT0 = 0,
    POT1 = 1,
    POT2 = 2,
    CV0 = 3,
    CV1 = 4,
    CV2 = 5,
} adc_channel_t;

/// @brief ADC configuration structure
/// @param ch ADC channel to get the value from
/// @return ADC value from the specified channel (10-bit resolution)
uint16_t get_adc(adc_channel_t ch);

#endif //_K_API_ADC_