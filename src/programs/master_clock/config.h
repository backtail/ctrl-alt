#ifndef _MASTER_CLK_CONFIG_H_
#define _MASTER_CLK_CONFIG_H_

#include "user_program.h"

#ifdef MASTER_CLK

#define OUTPUT0 DIGTAL_OUT
#define OUTPUT1 DIGTAL_OUT
#define OUTPUT2 DIGTAL_OUT

#define ADC_SAMPLE_RATE 100.0f

// unused
#define DAC_SAMPLE_RATE 0.0f
#define DAC_LATENCY 0

#endif
#endif