#ifndef _PHASE_ACC_H_
#define _PHASE_ACC_H_

#include "stdint.h"

typedef struct ACCUMUMALTOR
{
    uint32_t accumulator;
    uint32_t phase_increment;
    uint8_t divisor;
} phase_acc_t;

typedef struct LUT_INDEX
{
    uint16_t lut_size;
    uint16_t index;
    uint16_t next_index;
    uint16_t fraction;
    uint8_t fractional_bits;
} lut_index_t;

typedef struct LUT_ACCUMUMALTOR
{
    phase_acc_t acc;
    lut_index_t lut_i;

} lut_phase_acc_t;

void phase_acc_lut_init(lut_phase_acc_t *acc, uint16_t lut_size, uint8_t fractional_bits);
void phase_acc_lut_set_freq(lut_phase_acc_t *acc, uint32_t freq, uint16_t sample_rate);
void phase_acc_lut_set_freq_divisor(lut_phase_acc_t *acc, uint8_t divisor);
void phase_acc_lut_set_phase(lut_phase_acc_t *acc, uint32_t phase);
void phase_acc_lut_update_accumulator(lut_phase_acc_t *acc);
uint8_t get_sample_uint8_phase_acc_lut(lut_phase_acc_t *acc, uint8_t *lut);
#endif // _PHASE_ACC_H_