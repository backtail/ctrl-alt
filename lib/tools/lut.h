#ifndef _LUT_H_
#define _LUT_H_

#include "stdint.h"

/// @brief Generates a sine lookup table
/// @param lut_buffer Pointer to the buffer where the lookup table will be stored
/// @param lut_size Size of the lookup table
/// @details The lookup table is filled with 8-bit values representing a sine wave.
void lut_8_bit_sine(uint8_t *lut_buffer, const uint16_t lut_size);

#endif // _LUT_H_