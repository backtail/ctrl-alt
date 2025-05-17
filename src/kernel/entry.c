/// @file entry.c
/// @brief Main entry point for the STM8S microcontroller.

#include "hw_config.h"

#include "stm8s_clk.h"

// kernel hardware
#include "kernel/interrupts.h"
#include "kernel/hw/gpio.h"
#include "kernel/hw/adc.h"
#include "kernel/hw/dac.h"

/**
 * @brief
 *
 * This function configures the system clock, sets up input/output pins,
 * initializes ADC and DAC (if required), and calls user-defined setup/start
 * functions. It then enters an infinite loop, periodically handling DAC output
 * (if enabled) and calling the update function.
 *
 **/
void main(void)
{
    /// @todo Clock speed should be configured by API and make it exposed to the user
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz system clock

    setup_input_pins();
    setup_output_pins();
    setup_adc();
#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)
    setup_dac();
#endif

    setup(); // User-defined setup function

    enableInterrupts();

    start_adc();
#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)
    start_dac();
#endif

    start(); // User-defined start function

    while (1)
    {
#if (OUTPUT0 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT || OUTPUT2 == ANALOG_OUT)
        handle_dac();
#endif
        update(); // User-defined update function
    }
}