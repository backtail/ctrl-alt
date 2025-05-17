#ifndef _K_HW_DAC_
#define _K_HW_DAC_

#include "hw_config.h"

#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)

/// @brief Initializes the DAC hardware
/// @details This function sets up the DAC hardware, including the timer and
/// the output pins. It also initializes the DAC latency buffer and the ring
/// buffer for the DAC output, in case DAC_LATENCY > 1.
void setup_dac(void);

/// @brief Starts the DAC hardware
/// @details This function enables the DAC hardware and starts the timer.
/// It also sets up the interrupt for the DAC update.
void start_dac(void);

/// @brief Handles the DAC hardware in the main loop
void handle_dac(void);

#endif

#endif // _K_HW_DAC_