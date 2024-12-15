#include "user_program.h"

#ifdef MASTER_CLK

#include "kernel/interrupts.h"

#include "kernel/api/gpio.h"
#include "kernel/api/adc.h"
#include "kernel/api/dac.h"

void exti_it_callback() {}

void setup() {}

void start() {}

void update() {}

#endif // WAVETABLE_LFO