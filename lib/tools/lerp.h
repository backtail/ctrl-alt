#ifndef _LERP_H_
#define _LERP_H_

#include "stdint.h"

uint8_t lerp_8_bit_buffer(uint8_t *buffer, uint32_t alpha, uint16_t index, uint16_t next_index, const uint32_t fraction_bits);
uint8_t lerp_8_bit(uint8_t a, uint8_t b, uint16_t weight);
uint8_t interpolate_three_points(uint8_t a, uint8_t b, uint8_t c, uint16_t weight);

#endif // _LERP_H_