/*
	obsluga przyciskow w projekcie serwa
	mode - opcja wyboru trybu pracy serwa - zmienna definiowana i wykorzystywana w main
	pwm_btn - zmiana reczna poprzez przycisk sterowania serwa
	
	pinout:
	zwieranie do GND
	PC12	zmiana pwm_btn
	PC13	zmiana pwm_btn
	
	PB2 zmiana mode
*/

#ifndef BTN_H_
#define BTN_H_

#include <stm32f0xx.h>

#define STEP_BTN 50

extern uint8_t latch;
extern int mode;
extern int pwm_btn;

void init_btn(void);




#endif

