/// @file pin_config.h
/// @brief Pin configuration header file
/// @details This file contains the pin configuration for the project. It defines
/// the GPIO ports and pins for various components such as LEDs, switches,
/// pulse inputs, and pulse outputs. It also defines the pin polarity and
/// provides a structure to represent the pin configuration.

#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_

#include "stm8s.h"
#include "hw_config.h"

// MISC
#define HIGH 1
#define LOW 0

// LEDs
#define LED0_PORT GPIOF
#define LED0_PIN GPIO_PIN_4
#define LED1_PORT GPIOE
#define LED1_PIN GPIO_PIN_5
#define LED2_PORT GPIOD
#define LED2_PIN GPIO_PIN_7

// SWITCHES
#define MODE_SWITCH_PORT GPIOA
#define MODE_SWITCH_PIN GPIO_PIN_1
#define TRIGGER_SWITCH_PORT GPIOD
#define TRIGGER_SWITCH_PIN GPIO_PIN_6

// PULSE IN
#define PULSE0_IN_PORT GPIOD
#define PULSE0_IN_PIN GPIO_PIN_3
#define PULSE1_IN_PORT GPIOD
#define PULSE1_IN_PIN GPIO_PIN_4
#define PULSE2_IN_PORT GPIOD
#define PULSE2_IN_PIN GPIO_PIN_5

// PULSE OUT
#define PULSE0_OUT_PORT GPIOC
#define PULSE0_OUT_PIN GPIO_PIN_1
#define PULSE1_OUT_PORT GPIOC
#define PULSE1_OUT_PIN GPIO_PIN_2
#define PULSE2_OUT_PORT GPIOC
#define PULSE2_OUT_PIN GPIO_PIN_3

// PIN POLARITY
#define NON_INVERSED 0
#define INVERSED 1

// PIN STRUCT DEFINE

/// @brief Defines hardware configuration for a pin
typedef struct pin
{
    const bool polarity;     ///< Hardware inversion, either `NON-INVERSED` or `INVERSED`
    GPIO_TypeDef *port;      ///< GPIO port address
    const uint8_t pin_index; ///< Pin number
} pin_t;

// INPUT PINS

static pin_t MODE_SWITCH = {
    .polarity = INVERSED,
    .port = MODE_SWITCH_PORT,
    .pin_index = MODE_SWITCH_PIN};

static pin_t TRIGGER_SWITCH = {
    .polarity = INVERSED,
    .port = TRIGGER_SWITCH_PORT,
    .pin_index = TRIGGER_SWITCH_PIN};

static pin_t IN0 = {
    .polarity = INVERSED,
    .port = PULSE0_IN_PORT,
    .pin_index = PULSE0_IN_PIN};

static pin_t IN1 = {
    .polarity = INVERSED,
    .port = PULSE1_IN_PORT,
    .pin_index = PULSE1_IN_PIN};

static pin_t IN2 = {
    .polarity = INVERSED,
    .port = PULSE2_IN_PORT,
    .pin_index = PULSE2_IN_PIN};

// OUTPUTS PINS

static pin_t LED0 = {
    .polarity = NON_INVERSED,
    .port = LED0_PORT,
    .pin_index = LED0_PIN};

static pin_t LED1 = {
    .polarity = NON_INVERSED,
    .port = LED1_PORT,
    .pin_index = LED1_PIN};

static pin_t LED2 = {
    .polarity = NON_INVERSED,
    .port = LED2_PORT,
    .pin_index = LED2_PIN};

#if OUTPUT0 == DIGITAL_OUT
static pin_t OUT0 = {
    .polarity = NON_INVERSED,
    .port = PULSE0_OUT_PORT,
    .pin_index = PULSE0_OUT_PIN};
#endif

#if OUTPUT1 == DIGITAL_OUT
static pin_t OUT1 = {
    .polarity = NON_INVERSED,
    .port = PULSE1_OUT_PORT,
    .pin_index = PULSE1_OUT_PIN};
#endif

#if OUTPUT2 == DIGITAL_OUT
static pin_t OUT2 = {
    .polarity = NON_INVERSED,
    .port = PULSE2_OUT_PORT,
    .pin_index = PULSE2_OUT_PIN};
#endif

#endif // _PIN_CONFIG_H_