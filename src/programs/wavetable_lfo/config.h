#ifndef _WAVETABLE_LFO_CONFIG_H_
#define _WAVETABLE_LFO_CONFIG_H_

#include "user_program.h"

#ifdef WAVETABLE_LFO

#define OUTPUT0 ANALOG_OUT
#define OUTPUT1 ANALOG_OUT
#define OUTPUT2 ANALOG_OUT

#define ADC_SAMPLE_RATE 500.0f

#define DAC_SAMPLE_RATE 3000.0f
#define DAC_LATENCY 6

#endif
#endif