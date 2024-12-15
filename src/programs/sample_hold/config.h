#ifndef _SAMPLE_HOLD_CONFIG_
#define _SAMPLE_HOLD_CONFIG_

#include "user_program.h"

#ifdef SAMPLE_HOLD

#define OUTPUT0 ANALOG_OUT
#define OUTPUT1 ANALOG_OUT
#define OUTPUT2 ANALOG_OUT

#define ADC_SAMPLE_RATE 38000.0f // wtf
#define DAC_SAMPLE_RATE 38000.0f // wtf
#define DAC_LATENCY 1

#endif
#endif