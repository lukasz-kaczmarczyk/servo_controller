#include "btn.h"
#include "joystick.h"

/*
	konfiguracja przyciskow do obslugi serwa
*/

int mode = 0;
int pwm_btn = 500;
uint8_t latch = 0;
uint16_t counter = 0;

void init_btn(void){
		//interrupt PA4 BTN
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR4_0;//pullup
	NVIC_EnableIRQ(EXTI4_15_IRQn);
	EXTI->IMR |= EXTI_IMR_MR4;
	EXTI->FTSR |= EXTI_FTSR_TR4;

	
	//BTN conf: PB2, input, pullup
	RCC->APB2ENR |=  RCC_APB2ENR_SYSCFGCOMPEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR2_0;//pullup
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PB; 
	NVIC_EnableIRQ(EXTI2_3_IRQn);
	EXTI->IMR |= EXTI_IMR_MR2;
	EXTI->FTSR |= EXTI_FTSR_TR2;
	//EXTI->RTSR = EXTI_RTSR_TR2;
	
		//button pc12 pc13 przerwanie
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR12_0 | GPIO_PUPDR_PUPDR13_0;//pullup
	NVIC_EnableIRQ(EXTI4_15_IRQn);
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PC | SYSCFG_EXTICR4_EXTI13_PC; 
	EXTI->IMR |= EXTI_IMR_MR12 | EXTI_IMR_MR13;
	EXTI->FTSR |= EXTI_FTSR_TR12 | EXTI_FTSR_TR13;
}




//-----------------------------------------------------------------
//reakcja na zmiane opcji za pomoca przycisku
void EXTI2_3_IRQHandler(void){
	++mode;
	EXTI->PR = EXTI_PR_PR2;
}

void EXTI4_15_IRQHandler(void){
	switch(EXTI->PR){
		/*case EXTI_PR_PR4:
			EXTI->PR = EXTI_PR_PR4;
			print_signal();
		break;
		*/
		
		case EXTI_PR_PR13:
			EXTI->PR = EXTI_PR_PR13;
			pwm_btn += STEP_BTN;
			if( pwm_btn > 2500 )
				pwm_btn = 2500;
		break;
		case EXTI_PR_PR12:
			EXTI->PR = EXTI_PR_PR12;
			pwm_btn -= STEP_BTN;
			if( pwm_btn < 500 )
				pwm_btn = 500;
		break; 	
			//do obslugi joysticka, nie mozna w joystick stworzyc taka sama funkcje !!!
		case EXTI_PR_PR9:
			//latch ^= 0x01;
			while(++counter){}
			latch ^= 0x01;
			EXTI->PR = EXTI_PR_PR9;
		break;
	}
}
