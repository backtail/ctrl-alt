#include "hw_config.h"

#include "stm8s_clk.h"

// kernel hardware
#include "kernel/interrupts.h"
#include "kernel/hw/gpio.h"
#include "kernel/hw/adc.h"
#include "kernel/hw/dac.h"

void main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz system clock

    setup_input_pins();
    setup_output_pins();
    setup_adc();
#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)
    setup_dac();
#endif

    setup();

    enableInterrupts();

    start_adc();
#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)
    start_dac();
#endif

    start();

    while (1)
    {
#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)
        handle_dac();
#endif
        update();
    }
}