#include "user_program.h"

#ifdef BLINKY

#include "kernel/api/gpio.h"
#include "kernel/misc/delay.h"

uint8_t led_state = 1;

void set_all_pins(void)
{
    set_pin(&LED0, led_state & 0b001);
    set_pin(&LED1, led_state & 0b010);
    set_pin(&LED2, led_state & 0b100);

    set_pin(&OUT0, led_state & 0b001);
    set_pin(&OUT1, led_state & 0b010);
    set_pin(&OUT2, led_state & 0b100);
}

void setup()
{
}

void start() {}

void update()
{
    led_state <<= 1;
    if (led_state > (1 << 2))
        led_state = 1;

    set_all_pins();

    delay_us(500000);
}

#endif // BLINKY