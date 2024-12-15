#ifndef _WAVEFORMS_H_
#define _WAVEFORMS_H_

#include "stdint.h"

uint32_t uint_sine(float phase, const uint32_t max_val);
uint32_t uint_sawtooth(float phase, const uint32_t max_val);
uint32_t uint_triangle(float phase, const uint32_t max_val);
uint32_t uint_square(float phase, const uint32_t max_val);
uint32_t uint_steps(float phase, uint8_t n_steps, const uint32_t max_val);

#endif // _WAVEFORMS_H_