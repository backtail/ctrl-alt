#include "lerp.h"

uint8_t lerp_8_bit_buffer(uint8_t *buffer, uint32_t alpha, uint16_t index, uint16_t next_index, const uint32_t fraction_bits)
{
    // Retrieve LUT values
    uint8_t V1 = buffer[index];
    uint8_t V2 = buffer[next_index];

    // Perform linear interpolation
    return V1 + ((uint32_t)(alpha * (V2 - V1)) >> fraction_bits);
}

uint8_t lerp_8_bit(uint8_t a, uint8_t b, uint16_t weight)
{
    uint16_t complement_weight = 1023 - weight;

    // Compute weighted contributions
    uint32_t contrib1 = (uint32_t)complement_weight * a;
    uint32_t contrib2 = (uint32_t)weight * b;

    // Combine and normalize
    return (uint8_t)((contrib1 + contrib2) >> 10);
}

uint8_t interpolate_three_points(uint8_t a, uint8_t b, uint8_t c, uint16_t weight)
{
    uint8_t result;
    uint16_t W_prime;

    if (weight < 341)
    {
        // First interval: interpolate between LUT1 and LUT2
        W_prime = weight; // Local weight within this interval
        result = ((uint32_t)(341 - W_prime) * a + (uint32_t)W_prime * b) / 341;
    }
    else if (weight < 682)
    {
        // Second interval: interpolate between LUT2 and LUT3
        W_prime = weight - 341; // Local weight within this interval
        result = ((uint32_t)(341 - W_prime) * b + (uint32_t)W_prime * c) / 341;
    }
    else
    {
        // Third interval: extrapolate towards LUT3
        W_prime = weight - 682; // Local weight within this interval
        result = ((uint32_t)(341 - W_prime) * c + (uint32_t)W_prime * c) / 341;
    }

    return result;
}