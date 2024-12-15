#include "delay.h"

void delay_us(uint32_t delay_us)
{
    static volatile int b;

    for (uint32_t i = 0; i < delay_us; i++)
    {
        b++;
    }
}