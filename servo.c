#include "servo.h"
void conf_adc(void);


/*
	PA0 - TIM2_CH1
*/
void init_servo(void){
	//pwm out: PA0
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER0_1; //AF
	GPIOA->AFR[0] |= (1 << 1); //AF2
	
	//TIM2 conf: pwm, arr 20ms, f 1Mhz
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC  = TIM_PSC; //f tim2: 1Mhz
	TIM2->ARR = T_PWM; //20ms - okres sygnaBu
	TIM2->CR1 &= ~TIM_CR1_ARPE;
	TIM2->CCER |= TIM_CCER_CC1E;//?????? gdzie ze output, bit CC1P
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //111 stan L, stan H - PWM MODE 2
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE; //?
	TIM2->CR1 |= TIM_CR1_CEN;                         

	//conf_adc();
}

/* ADC conf: PC3 ADC_IN_13 additional function
	konfiguracja potencjometru - napiecie mierzone i obliczane pod adc
*/
void conf_adc(void){
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER3;
	ADC1->CHSELR |= ADC_CHSELR_CHSEL13;
	ADC1->CFGR1 |= ADC_CFGR1_CONT;
	ADC1->CFGR1 |= ADC_CFGR1_RES_1;	//res 8 BITOWA    
	ADC1->CR |= ADC_CR_ADEN;
	while( !(ADC1->ISR & ADC_ISR_ADRDY));
	ADC1->CR |= ADC_CR_ADSTART;
}

void stop_adc(void)
{
	ADC1->CR |= ADC_CR_ADSTP;
	
}


