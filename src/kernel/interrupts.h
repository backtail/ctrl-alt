
#ifndef _KERNEL_INTERRUPTS_
#define _KERNEL_INTERRUPTS_

#include "stm8s.h"

#define NULL_POINTER ((void *)0)

INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler);                /* TRAP */
INTERRUPT_HANDLER(TLI_IRQHandler, 0);                   /* TLI */
INTERRUPT_HANDLER(AWU_IRQHandler, 1);                   /* AWU */
INTERRUPT_HANDLER(CLK_IRQHandler, 2);                   /* CLOCK */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3);            /* EXTI PORTA */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4);            /* EXTI PORTB */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5);            /* EXTI PORTC */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6);            /* EXTI PORTD */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7);            /* EXTI PORTE */
INTERRUPT_HANDLER(SPI_IRQHandler, 10);                  /* SPI */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11); /* TIM1 UPD/OVF/TRG/BRK */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12);         /* TIM1 CAP/COM */
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13);     /* TIM2 UPD/OVF/BRK */
INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14);         /* TIM2 CAP/COM */
INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15);     /* TIM3 UPD/OVF/BRK */
INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16);         /* TIM3 CAP/COM */
INTERRUPT_HANDLER(I2C_IRQHandler, 19);                  /* I2C */
INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20);             /* UART2 TX */
INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21);             /* UART2 RX */
INTERRUPT_HANDLER(ADC1_IRQHandler, 22);                 /* ADC1 */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23);         /* TIM4 UPD/OVF */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24);           /* EEPROM ECC CORRECTION */

// these function pointers can be used by user programs
extern void (*it_exti_portd_handler)(void);
extern void (*it_tim1_upd_ovf_brk_handler)(void);
extern void (*it_tim3_upd_ovf_brk_handler)(void);

#endif /* _KERNEL_INTERRUPTS_ */