#ifndef _K_API_DAC_
#define _K_API_DAC_

#include "hw_config.h"

#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)

#include "stdint.h"

extern void (*dac_callback)(void);

#if OUTPUT0 == ANALOG_OUT
void set_dac0(uint8_t val);
#endif

#if OUTPUT1 == ANALOG_OUT
void set_dac1(uint8_t val);
#endif

#if OUTPUT2 == ANALOG_OUT
void set_dac2(uint8_t val);
#endif

#endif

#endif // _K_API_DAC_