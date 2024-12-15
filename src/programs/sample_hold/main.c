#include "user_program.h"

#ifdef SAMPLE_HOLD

#include "kernel/interrupts.h"

#include "kernel/api/gpio.h"
#include "kernel/api/adc.h"
#include "kernel/api/dac.h"

uint8_t dac0_sample = 0;
uint8_t dac1_sample = 0;
uint8_t dac2_sample = 0;

void exti_callback()
{
    if (read_pin(&IN0))
    {
        dac0_sample = get_adc(CV0) >> 2;
        set_pin(&LED0, HIGH);
        return;
    }

    if (read_pin(&IN1))
    {
        dac1_sample = get_adc(CV1) >> 2;
        set_pin(&LED1, HIGH);
        return;
    }

    if (read_pin(&IN2))
    {
        dac2_sample = get_adc(CV2) >> 2;
        set_pin(&LED2, HIGH);
        return;
    }

    // manually hold all samples
    if (read_pin(&TRIGGER_SWITCH))
    {
        dac0_sample = get_adc(CV0) >> 2;
        dac1_sample = get_adc(CV1) >> 2;
        dac2_sample = get_adc(CV2) >> 2;

        set_pin(&LED0, HIGH);
        set_pin(&LED1, HIGH);
        set_pin(&LED2, HIGH);
    }

    // falling edge
    set_pin(&LED0, LOW);
    set_pin(&LED1, LOW);
    set_pin(&LED2, LOW);
}

void callback()
{
    set_dac0(dac0_sample);
    set_dac1(dac1_sample);
    set_dac2(dac2_sample);
}

void setup()
{
    // assign callbacks
    dac_callback = callback;
    it_exti_portd_handler = exti_callback;
}

void start() {}

void update() {}

#endif // WAVETABLE_LFO