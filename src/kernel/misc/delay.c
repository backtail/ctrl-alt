#include "delay.h"

void delay_us(uint32_t delay_us)
{
    static volatile int b;

    /// @todo This is not accurate and should be replaced with a more precise
    /// timing method. This is just a placeholder for now.
    for (uint32_t i = 0; i < delay_us; i++)
    {
        b++;
    }
}