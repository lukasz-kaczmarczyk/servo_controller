#include "joystick.h"

/*
	PB9 interrupt
	zatrzaskiwanie wartosci poprzez przycisk PB9
*/
//uint8_t latch = 0;
void init_joy(void)
{
	//latch = 0;
	RCC->APB2ENR |=  RCC_APB2ENR_SYSCFGCOMPEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR9_0;//pullup
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI9_PB; 
	NVIC_EnableIRQ(EXTI4_15_IRQn);
	EXTI->IMR |= EXTI_IMR_MR9;
	EXTI->FTSR |= EXTI_FTSR_TR9;
}

/* ADC conf: PC0 ADC_IN_10 additional function
	konfiguracja potencjometru - napiecie mierzone i obliczane pod adc
*/
  void conf_adc_joy(void){
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER0;
	ADC1->CHSELR |= ADC_CHSELR_CHSEL10;
	ADC1->CFGR1 |= ADC_CFGR1_CONT;
	ADC1->CFGR1 |= ADC_CFGR1_RES_1;	//res 8 BITOWA
	ADC1->CR |= ADC_CR_ADEN;
	while( !(ADC1->ISR & ADC_ISR_ADRDY));
	ADC1->CR |= ADC_CR_ADSTART;
}

void stop_adc_joy(void)
{
	ADC1->CR |= ADC_CR_ADSTP;
	
}

//reakcja na zatrzask - przycisk w joystick: PB9
/*
void EXTI4_15_IRQHandler(void){
		//++mode;
	latch ^= 0x01;
	EXTI->PR = EXTI_PR_PR9;
}
*/


