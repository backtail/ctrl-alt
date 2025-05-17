#ifndef _WAVEFORMS_H_
#define _WAVEFORMS_H_

#include "stdint.h"

/// @brief calculates the value of a sine wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_sine(float phase, const uint32_t max_val);

/// @brief calculates the value of a sawtooth wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_sawtooth(float phase, const uint32_t max_val);

/// @brief calculates the value of a triangle wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_triangle(float phase, const uint32_t max_val);

/// @brief calculates the value of a square wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_square(float phase, const uint32_t max_val);

/// @brief calculates the value of a square wave depending on phasor
/// @param phase between 0.0f and 1.0f for a full cycle
/// @param n_steps number of steps
/// @param max_val has to be a constant
/// @return value between 0 and `max_val`
uint32_t uint_steps(float phase, uint8_t n_steps, const uint32_t max_val);

#endif // _WAVEFORMS_H_