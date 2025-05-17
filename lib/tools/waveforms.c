#include "waveforms.h"

#include "math.h"
#include "consts.h"

uint32_t uint_sine(float phase, const uint32_t max_val)
{
    return (uint32_t)(((sinf(phase * 2.0f * M_PI - M_PI / 2.0f) / 2.0f) + 0.5f) * max_val);
}

uint32_t uint_sawtooth(float phase, const uint32_t max_val)
{
    return phase * max_val;
}

uint32_t uint_triangle(float phase, const uint32_t max_val)
{
    return (1.0f - fabsf((2.0f * phase) - 1.0f)) * max_val;
}

uint32_t uint_square(float phase, const uint32_t max_val)
{
    return (floorf(1.999999f * phase) * max_val);
}

uint32_t uint_steps(float phase, uint8_t n_steps, const uint32_t max_val)
{
    return (floorf(phase * n_steps) / (n_steps - 1)) * max_val;
}