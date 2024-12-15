#include "phase_accumulator.h"

#include "lerp.h"

void phase_acc_lut_init(lut_phase_acc_t *acc, uint16_t lut_size, uint8_t fractional_bits)
{
    acc->acc.accumulator = 0;
    acc->acc.phase_increment = 0;
    acc->acc.divisor = 0;
    acc->lut_i.lut_size = lut_size;
    acc->lut_i.fractional_bits = fractional_bits;
    acc->lut_i.index = 0;
    acc->lut_i.next_index = 1;
    acc->lut_i.fraction = 0;
}

void phase_acc_lut_set_freq_divisor(lut_phase_acc_t *acc, uint8_t divisor)
{
    acc->acc.divisor = divisor;
}

void phase_acc_lut_set_freq(lut_phase_acc_t *acc, uint32_t freq, uint16_t sample_rate)
{
    acc->acc.phase_increment = ((uint32_t)(freq * acc->lut_i.lut_size * (uint32_t)(1UL << acc->lut_i.fractional_bits)) / (uint32_t)sample_rate) >> acc->acc.divisor;
}

void phase_acc_lut_set_phase(lut_phase_acc_t *acc, uint32_t phase)
{
    acc->acc.accumulator = phase;
}

void phase_acc_lut_update_accumulator(lut_phase_acc_t *acc)
{
    acc->acc.accumulator += acc->acc.phase_increment;
    acc->acc.accumulator %= ((uint32_t)acc->lut_i.lut_size << acc->lut_i.fractional_bits);

    acc->lut_i.index = acc->acc.accumulator >> acc->lut_i.fractional_bits;                  // Integer part
    acc->lut_i.next_index = acc->lut_i.index % acc->lut_i.lut_size;                         // Wrap around
    acc->lut_i.fraction = acc->acc.accumulator & ((1UL << acc->lut_i.fractional_bits) - 1); // Fractional part
}

uint8_t get_sample_uint8_phase_acc_lut(lut_phase_acc_t *acc, uint8_t *lut)
{
    return lerp_8_bit_buffer(lut, acc->lut_i.fraction, acc->lut_i.index, acc->lut_i.next_index, acc->lut_i.fractional_bits);
}
