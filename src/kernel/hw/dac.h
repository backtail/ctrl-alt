#ifndef _K_HW_DAC_
#define _K_HW_DAC_

#include "hw_config.h"

#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)

void setup_dac(void);
void start_dac(void);
void handle_dac(void);

#endif

#endif // _K_HW_DAC_