#ifndef _K_API_GPIO_
#define _K_API_GPIO_

#include "kernel/pin_config.h"

/// @brief Sets the pin to either high or low, respecting polarity (on PCB)
/// @param p pin struct reference
/// @param state either 0 or 1
inline void set_pin(pin_t *p, bool state)
{
    if (state ^ p->polarity)
        p->port->ODR |= (uint8_t)p->pin_index;
    else
        p->port->ODR &= (uint8_t)(~(p->pin_index));
}

/// @brief Reads the input on a certain pin, respecting polarity (on PCB)
/// @param p pin struct reference
/// @return state of input pin, respecting polarity (on PCB)
inline bool read_pin(pin_t *p)
{
    if (p->port->IDR & (uint8_t)p->pin_index)
        return 1 ^ p->polarity;
    else
        return 0 ^ p->polarity;
}

#endif // _K_API_GPIO_