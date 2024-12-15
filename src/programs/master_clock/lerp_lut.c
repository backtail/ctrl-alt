#include "lut.h"

// Linear interpolation function for uint16_t
uint16_t linear_interpolate(uint16_t x, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    if (x1 == x0)
    {
        // Avoid division by zero; return y0 (or y1, they should be the same if x1 == x0)
        return y0;
    }

    // Perform linear interpolation
    // Formula: y = y0 + ((x - x0) * (y1 - y0)) / (x1 - x0)
    uint32_t numerator = (uint32_t)(x - x0) * (y1 - y0);
    uint16_t result = y0 + numerator / (x1 - x0);

    return result;
}

uint16_t interpolate_lut(uint16_t i_index, const uint16_t *LUT, const uint16_t max_index, const uint16_t lut_size)
{
    // No need to interpolate
    if (i_index == 0)
    {
        return LUT[0];
    }

    // Ensure the i_index is within range
    if (i_index > max_index)
    {
        return LUT[lut_size - 1];
    }

    // Determine LUT index range
    uint16_t index = i_index * (lut_size - 1) / (max_index + 1); // Map i_index to LUT index
    uint16_t next_index = (index == (lut_size - 1)) ? (lut_size - 1) : index + 1;

    // Get x0, y0 and x1, y1 for interpolation
    uint16_t x0 = index * (max_index) / (lut_size - 1);      // Input value corresponding to LUT[index]
    uint16_t y0 = LUT[index];                                // LUT value at index
    uint16_t x1 = next_index * (max_index) / (lut_size - 1); // Input value corresponding to LUT[next_index]
    uint16_t y1 = LUT[next_index];                           // LUT value at next_index

    return linear_interpolate(i_index, x0, y0, x1, y1);
}