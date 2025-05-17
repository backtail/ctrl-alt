#ifndef _LERP_H_
#define _LERP_H_

#include "stdint.h"

/// @brief Linear interpolation function for 8-bit values with fractional arthmetic
/// @param buffer Pointer to the buffer containing the values
/// @param alpha Fractional value for interpaltion
/// @param index Index of the first value
/// @param next_index Index of the second value
/// @param fraction_bits Number of bits used for the fraction
/// @return Interpolated value
uint8_t lerp_8_bit_buffer(uint8_t *buffer, uint32_t alpha, uint16_t index, uint16_t next_index, const uint32_t fraction_bits);

/// @brief Linear interpolation function for 8-bit values
/// @param a First value
/// @param b Second value
/// @param weight Weight for the interpolation (0-1023)
/// @return Interpolated value
uint8_t lerp_8_bit(uint8_t a, uint8_t b, uint16_t weight);

/// @brief Interpolates between three points
/// @param a First value
/// @param b Second value
/// @param c Third value
/// @param weight Weight for the interpolation (0-1023), divided into three intervals
/// @return Interpolated value
uint8_t interpolate_three_points(uint8_t a, uint8_t b, uint8_t c, uint16_t weight);

#endif // _LERP_H_