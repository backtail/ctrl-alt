#include "user_program.h"

#include "kernel/interrupts.h"

#include "kernel/api/gpio.h"
#include "kernel/api/adc.h"
#include "kernel/api/dac.h"

#include "lerp.h"
#include "phase_accumulator.h"
#include "waveforms.h"
#include "math.h"

#define LUT_SIZE 421UL
#define FRACTIONAL_BITS 16 // amount fractional bits of accumulator

// LUTs
uint8_t saw[LUT_SIZE] = {0};
uint8_t sine[LUT_SIZE] = {0};
uint8_t tri[LUT_SIZE] = {0};
uint8_t steps[LUT_SIZE] = {0};

lut_phase_acc_t acc0;
lut_phase_acc_t acc1_2;

void exti_it_callback()
{
    // states of the inputs
    bool in0 = read_pin(&IN0);
    bool in1 = read_pin(&IN1);
    bool in2 = read_pin(&IN2);
    bool trig_sw = read_pin(&TRIGGER_SWITCH);

    if (in0 || in2 || trig_sw)
        phase_acc_lut_set_phase(&acc0, 0); // reset LFO

    if (in1 || in2 || trig_sw)
        phase_acc_lut_set_phase(&acc1_2, 0); // reset LFO

    // indicate reset
    set_pin(&LED0, in0);
    set_pin(&LED1, in1);
    set_pin(&LED2, in2 || trig_sw);
}

void callback()
{
    static uint8_t freq_divisor;

    if (read_pin(&MODE_SWITCH))
        freq_divisor = 3; // fast
    else
        freq_divisor = 7; // slow

    phase_acc_lut_set_freq_divisor(&acc0, freq_divisor);
    phase_acc_lut_set_freq_divisor(&acc1_2, freq_divisor);

    phase_acc_lut_set_freq(&acc0, (get_adc(POT0) + get_adc(CV0) + 60) >> 3, (uint16_t)DAC_SAMPLE_RATE);
    phase_acc_lut_set_freq(&acc1_2, (get_adc(POT1) + get_adc(CV1) + 60) >> 3, (uint16_t)DAC_SAMPLE_RATE);

    for (uint16_t l = 0; l < DAC_LATENCY; l++)
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // LFO 0
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        phase_acc_lut_update_accumulator(&acc0);

        uint8_t saw_sample = get_sample_uint8_phase_acc_lut(&acc0, saw);

        set_dac0(saw_sample);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // LFO 1 & 2
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        phase_acc_lut_update_accumulator(&acc1_2);

        uint8_t tri_sample = get_sample_uint8_phase_acc_lut(&acc1_2, tri);
        uint8_t sine_sample = get_sample_uint8_phase_acc_lut(&acc1_2, sine);
        uint8_t steps_sample = get_sample_uint8_phase_acc_lut(&acc1_2, steps);

        set_dac1(tri_sample);

        uint16_t wavetable_pos = get_adc(POT2) + get_adc(CV2);

        if (wavetable_pos > 1023)
            wavetable_pos = 1023;

        uint8_t wave_table_sample = lerp_8_bit(sine_sample, steps_sample, wavetable_pos);

        set_dac2(wave_table_sample);
    }
}

void setup()
{
    for (int i = 0; i < LUT_SIZE; i++)
    {
        float inc = 1.0f / (LUT_SIZE - 1);
        float phase = i * inc;

        saw[i] = (uint8_t)uint_sawtooth(phase, UINT8_MAX);
        sine[i] = (uint8_t)uint_sine(phase, UINT8_MAX);
        tri[i] = (uint8_t)uint_triangle(phase, UINT8_MAX);
        steps[i] = (uint8_t)uint_steps(phase, 6, UINT8_MAX);
    }

    phase_acc_lut_init(&acc0, LUT_SIZE, FRACTIONAL_BITS);
    phase_acc_lut_init(&acc1_2, LUT_SIZE, FRACTIONAL_BITS);

    // assign callbacks
    dac_callback = callback;
    it_exti_portd_handler = exti_it_callback;
}

void start() {}

void update() {}