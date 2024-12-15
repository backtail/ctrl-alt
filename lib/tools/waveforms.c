#include "waveforms.h"

#include "math.h"
#include "consts.h"

/// @brief calculates the value of a sine wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_sine(float phase, const uint32_t max_val)
{
    return (uint32_t)(((sinf(phase * 2.0f * M_PI - M_PI / 2.0f) / 2.0f) + 0.5f) * max_val);
}

/// @brief calculates the value of a sawtooth wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_sawtooth(float phase, const uint32_t max_val)
{
    return phase * max_val;
}

/// @brief calculates the value of a triangle wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_triangle(float phase, const uint32_t max_val)
{
    return (1.0f - fabsf((2.0f * phase) - 1.0f)) * max_val;
}

/// @brief calculates the value of a square wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_square(float phase, const uint32_t max_val)
{
    return (floorf(1.999999f * phase) * max_val);
}

/// @brief calculates the value of a square wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param n_steps number of steps
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_steps(float phase, uint8_t n_steps, const uint32_t max_val)
{
    return (floorf(phase * n_steps) / (n_steps - 1)) * max_val;
}