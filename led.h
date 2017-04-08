/*
	obsluga diod led na makiecie stm32discovery
	podlaczenie:
	LED1	PC6
	LED2	PC7
	LED3	PC8
	LED4	PC9
*/

#ifndef LED_H_
#define LED_H_

#include <stm32f0xx.h>

#define LED1 (1 << 6)
#define LED2 (1 << 8)
#define LED3 (1 << 7)
#define LED4 (1 << 9)
#define LEDS ( LED1 | LED2 | LED3 | LED4 )

#define leds_off GPIOC->BRR |= LEDS
#define led1_on GPIOC->BSRR |= LED1
#define led2_on GPIOC->BSRR |= LED2
#define led3_on GPIOC->BSRR |= LED3
#define led4_on GPIOC->BSRR |= LED4

#define led1_off GPIOC->BRR |= LED1
#define led2_off GPIOC->BRR |= LED2
#define led3_off GPIOC->BRR |= LED3
#define led4_off GPIOC->BRR |= LED4

void init_led(void);

#endif

