/*sterowanie serwem

	potencjometr PC3 ADC_IN_13
	sygnaB wyjsiowy PA0 TIM2_CH2

*/

#ifndef SERVO_H_
#define SERVO_H_

#include <stm32f0xx.h>
//number = 34;

#define TIM_PSC 48 // dla fcpu = 48MHz / 48
#define MAX_PWM 2500
#define MIN_PWM 500
#define NEUTRUM 1500
#define T_PWM 20000


void init_servo(void);
void conf_adc(void);
void stop_adc(void);

#endif
