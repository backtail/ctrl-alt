#include "lut.h"

#include "waveforms.h"

void lut_8_bit_sine(uint8_t *lut_buffer, const uint16_t lut_size)
{
    for (int i = 0; i < lut_size; i++)
    {
        float inc = 1.0f / (lut_size - 1);
        float phase = i * inc;

        lut_buffer[i] = (uint8_t)uint_sine(phase, UINT8_MAX);
    }
}
