#ifndef _PHASE_ACC_H_
#define _PHASE_ACC_H_

#include "stdint.h"

/// @brief Phase accumulator structure
typedef struct ACCUMUMALTOR
{
    uint32_t accumulator;     ///< Phase accumulator value
    uint32_t phase_increment; ///< Phase increment value
    uint8_t divisor;          ///< Divisor for frequency scaling
} phase_acc_t;

/// @brief Lookup table index structure
typedef struct LUT_INDEX
{
    uint16_t lut_size;       ///< Size of the lookup table
    uint16_t index;          /// Current index in the lookup table
    uint16_t next_index;     ///< Next index in the lookup table
    uint16_t fraction;       ///< Fractional part of the index
    uint8_t fractional_bits; ///< Number of bits used for the fractional part
} lut_index_t;

/// @brief Phase accumulator with lookup table index
typedef struct LUT_ACCUMUMALTOR
{
    phase_acc_t acc;   ///< Phase accumulator
    lut_index_t lut_i; ///< Lookup table index

} lut_phase_acc_t;

/// @brief Initializes the phase accumulator with a lookup table
/// @param acc Pointer to the phase accumulator structure
/// @param lut_size Size of the lookup table
/// @param fractional_bits Number of bits used for the fractional part
void phase_acc_lut_init(lut_phase_acc_t *acc, uint16_t lut_size, uint8_t fractional_bits);

/// @brief Sets the frequency divisor for the phase accumulator
/// @param acc Pointer to the phase accumulator structure
/// @param divisor Divisor value for frequency scaling
void phase_acc_lut_set_freq_divisor(lut_phase_acc_t *acc, uint8_t divisor);

/// @brief Sets the frequency for the phase accumulator
/// @param acc Pointer to the phase accumulator structure
/// @param freq Frequency value to set (in Hz)
/// @param sample_rate Sample rate value (in Hz)
void phase_acc_lut_set_freq(lut_phase_acc_t *acc, uint32_t freq, uint16_t sample_rate);

/// @brief Sets the phase for the phase accumulator
/// @param acc Pointer to the phase accumulator structure
/// @param phase Phase value to set (in fractional format)
void phase_acc_lut_set_phase(lut_phase_acc_t *acc, uint32_t phase);

/// @brief Updates the phase accumulator and calculates the next index
/// @param acc Pointer to the phase accumulator structure
void phase_acc_lut_update_accumulator(lut_phase_acc_t *acc);

/// @brief Gets the current sample from the lookup table
/// @param acc Pointer to the phase accumulator structure
/// @param lut Pointer to the lookup table
/// @return The current sample from the lookup table
uint8_t get_sample_uint8_phase_acc_lut(lut_phase_acc_t *acc, uint8_t *lut);

#endif // _PHASE_ACC_H_