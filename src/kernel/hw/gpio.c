#include "kernel/api/gpio.h"

#include "stm8s_gpio.h"

/// @brief Inits all GPIO input pins to their functions.
void setup_input_pins(void)
{
    GPIO_Init(MODE_SWITCH.port, MODE_SWITCH.pin_index, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(TRIGGER_SWITCH.port, TRIGGER_SWITCH.pin_index, GPIO_MODE_IN_PU_IT);
    GPIO_Init(IN0.port, IN0.pin_index, GPIO_MODE_IN_PU_IT);
    GPIO_Init(IN1.port, IN1.pin_index, GPIO_MODE_IN_PU_IT);
    GPIO_Init(IN2.port, IN2.pin_index, GPIO_MODE_IN_PU_IT);

    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL);
}

/// @brief Inits all GPIO output pins to their functions.
void setup_output_pins(void)
{
    GPIO_Init(LED0.port, LED0.pin_index, GPIO_MODE_OUT_PP_LOW_FAST);
    set_pin(&LED0, LOW);

    GPIO_Init(LED1.port, LED1.pin_index, GPIO_MODE_OUT_PP_LOW_FAST);
    set_pin(&LED1, LOW);

    GPIO_Init(LED2.port, LED2.pin_index, GPIO_MODE_OUT_PP_LOW_FAST);
    set_pin(&LED2, LOW);

#if OUTPUT0 == DIGITAL_OUT
    GPIO_Init(OUT0.port, OUT0.pin_index, GPIO_MODE_OUT_PP_LOW_FAST);
    set_pin(&OUT0, LOW);
#endif

#if OUTPUT1 == DIGITAL_OUT
    GPIO_Init(OUT1.port, OUT1.pin_index, GPIO_MODE_OUT_PP_LOW_FAST);
    set_pin(&OUT1, LOW);
#endif

#if OUTPUT2 == DIGITAL_OUT
    GPIO_Init(OUT2.port, OUT2.pin_index, GPIO_MODE_OUT_PP_LOW_FAST);
    set_pin(&OUT2, LOW);
#endif
}