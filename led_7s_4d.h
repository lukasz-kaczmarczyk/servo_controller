/*opis programu
	obsluga wyswietlacza 7 segmentowego, 4 cyfry, wspolna Anoda
	wykorzystanie rejestru przesuwnego 74hc164n
	
	podlaczenie:
	DSB: PC10
	CP: PC11
	
	anody cyfr:
	D1 PB3
	D2 PB4
	D3 PB5
	D4 PB6
	
	uwagi:
	przy uzywaniu jednej cyfry wazne jest, aby przed wysylaniem sekwencji cyfry wylaczyc wyswietlacz
	tj anode konkretnej cyfry - zapobiega to powstawaniu duchow
	
	rowniez przy multipleksowaniu, wysylac cyfre przy wylaczonej kazdej anodzie!!!
*/


#ifndef LED_7S_4D_H_
#define LED_7S_4D_H_

#include <stm32f0xx.h>

//pinout conf 74hc164n
#define DSB ( 1 << 10 )
#define CP ( 1 << 11 )

//spi programowy
#define SPI_PORT GPIOC
#define DATA (1 << 10)
#define CLK (1 << 11)

//konfiguracja timera TIM7
#define TIM_PSC 48 //48MHz / 48
#define TIM_ARR 5000 //czas przelaczania w x * us - 5ms

#define switch_off 	GPIOB->BRR |= GPIO_BRR_BR_3 | GPIO_BRR_BR_4 | GPIO_BRR_BR_5 |  GPIO_BRR_BR_6
#define clk_low GPIOC->BRR |= CLK
#define clk_high GPIOC->BSRR |= CLK


extern volatile int number;

//funkcje

/*
	inicjalizacja wyswietlacza led
	
	param ar - szybkosc przelaczania do nastepnej cyfry w ms
	pod warunkiem pracy timera z czestotliwoscia 1MHz
*/
void init_led7s(int ar);
/*
void spi_send(int cyfra);
void clear_led(void);
void tim7_conf(void);
void num_disp4(void);
*/
#endif /* LED4_H_ */
