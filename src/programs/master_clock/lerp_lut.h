#ifndef _LERP_LUT_H_
#define _LERP_LUT_H_

#include "stdint.h"

uint16_t linear_interpolate(uint16_t x, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

uint16_t interpolate_lut(uint16_t i_index, const uint16_t *LUT, const uint16_t max_index, const uint16_t lut_size);

#endif //_LERP_LUT_H_
