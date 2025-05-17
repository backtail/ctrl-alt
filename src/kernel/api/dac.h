#ifndef _K_API_DAC_
#define _K_API_DAC_

#include "hw_config.h"

#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)

#include "stdint.h"

extern void (*dac_callback)(void);

#if OUTPUT0 == ANALOG_OUT
/// @brief Sets the DAC output value for channel 0
/// @details This function sets the DAC output value for channel 0. If DAC_LATENCY
/// is greater than 1, the value is added to a ring buffer. Otherwise, it is set
/// directly in the latency buffer.
/// @param val The value to set for the DAC output (0-255)
void set_dac0(uint8_t val);
#endif

#if OUTPUT1 == ANALOG_OUT
/// @brief Sets the DAC output value for channel 1
/// @details This function sets the DAC output value for channel 1. If DAC_LATENCY
/// is greater than 1, the value is added to a ring buffer. Otherwise, it is set
/// directly in the latency buffer.
/// @param val The value to set for the DAC output (0-255)
void set_dac1(uint8_t val);
#endif

#if OUTPUT2 == ANALOG_OUT
/// @brief Sets the DAC output value for channel 2
/// @details This function sets the DAC output value for channel 2. If DAC_LATENCY
/// is greater than 1, the value is added to a ring buffer. Otherwise, it is set
/// directly in the latency buffer.
/// @param val The value to set for the DAC output (0-255)
void set_dac2(uint8_t val);
#endif

#endif

#endif // _K_API_DAC_