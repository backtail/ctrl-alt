/// @file interrupts.c
/// @brief Interrupt handlers for the STM8S microcontroller

#include "interrupts.h"

/////////////////////////////
// KERNELSPACE IT HANDLERS //
/////////////////////////////

void (*it_adc_handler)(void) = NULL_POINTER;
void (*it_tim2_upd_ovf_brk_handler)(void) = NULL_POINTER;

///////////////////////////
// USERSPACE IT HANDLERS //
///////////////////////////

void (*it_exti_portd_handler)(void) = NULL_POINTER;
void (*it_tim1_upd_ovf_brk_handler)(void) = NULL_POINTER;
void (*it_tim3_upd_ovf_brk_handler)(void) = NULL_POINTER;

INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler) {}
INTERRUPT_HANDLER(TLI_IRQHandler, 0) {}
INTERRUPT_HANDLER(AWU_IRQHandler, 1) {}
INTERRUPT_HANDLER(CLK_IRQHandler, 2) {}
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3) {}
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4) {}
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5) {}
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6) { it_exti_portd_handler(); }
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7) {}
INTERRUPT_HANDLER(SPI_IRQHandler, 10) {}
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11) { it_tim1_upd_ovf_brk_handler(); }
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12) {}
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13) { it_tim2_upd_ovf_brk_handler(); }
INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14) {}
INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15) { it_tim3_upd_ovf_brk_handler(); }
INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16) {}
INTERRUPT_HANDLER(I2C_IRQHandler, 19) {}
INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20) {}
INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21) {}
INTERRUPT_HANDLER(ADC1_IRQHandler, 22) { it_adc_handler(); }
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) {}
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24) {}
