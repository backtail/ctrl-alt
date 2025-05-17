/// @file hw_config.h
/// @brief Hardware configuration for the project
/// @details This file contains the hardware configuration settings for the
/// project. It includes definitions for CPU frequency, maximum prescaler
/// divisor, maximum counter value, and includes configuration files for
/// different programs. The configuration files are specific to the
/// functionality of each program, such as wavetable LFO, blinky, sample hold,
/// and master clock.

#ifndef _CTRL_ALT_HW_CONFIG_
#define _CTRL_ALT_HW_CONFIG_

#define DIGITAL_OUT 0
#define ANALOG_OUT 1

/// @todo This should be defined in the program configuration & part of the API
#define CPU_FREQ 16000000

#define MAX_PRESCALER_DIVISOR 15
#define MAX_COUNTER_VALUE UINT16_MAX

///////////////////////////////////////////////////////////////////////////////////////

// Every program should have its own config file
// and include it here
// This way we can have a single hw_config.h file
// that includes all the program config files
// This is a good practice to keep the code organized
// and maintainable

#include "programs/wavetable_lfo/config.h"
#include "programs/blinky/config.h"
#include "programs/sample_hold/config.h"
#include "programs/master_clock/config.h"

///////////////////////////////////////////////////////////////////////////////////////

#endif // _CTRL_ALT_HW_CONFIG_