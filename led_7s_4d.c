#include "led_7s_4d.h"
//#include <stm32f0xx.h>

const uint8_t cyfry[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

int j;
volatile int d = 0;
int bb = 0;
int abc = 0;
int arr;
volatile int number = 0;

uint8_t tmp1, tmp2, tmp3, tmp4;

void clear_led(void);
void tim7_conf(void);

void init_led7s(int ar){
	arr = 1000 * ar;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0;
	
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;
	GPIOB->BRR |= GPIO_BRR_BR_3 | GPIO_BRR_BR_4 | GPIO_BRR_BR_5 | GPIO_BRR_BR_6;
	
	clear_led();
	tim7_conf();
}



void clear_led(void){
	uint8_t tmp = 0;
	GPIOC->BSRR |= DSB;
	for( tmp = 0; tmp < 9; ++tmp ){
		GPIOC->BRR |= CP;
		GPIOC->BSRR |= CP;
	}
}


/*tim7 - odpowiedzialny za multipleksowanie, przerwanie,
	zdarzeniem jest przepelnienie rejestru liczacego
	( fcpu/PSC ) * ARR
*/

void tim7_conf(void){

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	TIM7->CR1 &= ~TIM_CR1_ARPE;
	TIM7->PSC = TIM_PSC;
	TIM7->ARR = arr;
	TIM7->DIER |= TIM_DIER_UIE;
	TIM7->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM7_IRQn);
	
}

/*
	wyslanie cyfry na wyswietlacz
*/
	void spi_send(int cyfra) {
		int i = 0;
		int znak = cyfry[cyfra];
		for(i = 7; i > -1; i--)
		{ clk_low;
			if((znak >> i) & 0x01) SPI_PORT->ODR |= DATA;
			else  { SPI_PORT -> ODR &= ~DATA; }
			clk_high;
		}
		
	}

/*
	wyswietlenie liczby na wyswietlaczu czterocyfrowym LED
*/
void num_disp4(){
	if( number > 9999){
		
	}else{
	  tmp1 = number/1000;
	  tmp2 = (number/100) % 10;
	  tmp3 = (number / 10) % 10;
	  tmp4 = number % 10;
		
		switch(d){
			//pierwsza cyfra
			case 1:
				switch_off;
				spi_send(tmp1);
				GPIOB->BSRR |= GPIO_BSRR_BS_3;
			break;
			case 2:
			  switch_off;
				spi_send(tmp2);
				GPIOB->BSRR |= GPIO_BSRR_BS_4;
			break;
			case 3:
			  switch_off;
				spi_send(tmp3);
				GPIOB->BSRR |= GPIO_BSRR_BS_5;
			break;
			case 4:
			  switch_off;
				spi_send(tmp4);
				GPIOB->BSRR |= GPIO_BSRR_BS_6;
			break;
			default:
				//d = 0;
			break;
		}
  }
}




//przerwanie odpowiedzialne za szybkosc przelaczania cyfr - multipleksowanie

void TIM7_IRQHandler(void){
	++d;
	if(d > 4) d = 1;
	num_disp4();
	TIM7->SR = 0;
}



