/*
	parametry:
	number - number do wyswietlenia
	mode - tryb pracy
*/
#include <stm32f0xx.h>
#include "led_7s_4d.h"
#include "servo.h"
#include "btn.h"
#include "led.h"
#include "joystick.h"
#include "hd44780.h"

void wait_us(int czas);
void wait_ms(int time);
//zmienna globalna, pokazuje wartosc jaka ma byc na wyswietlaczu
//volatile int number = 0; //number do wyswietlenia
//extern int mode; //tryb pracy

int pwm1;						//dla sterowania recznego
int pwm2 = MIN_PWM;	//dla sterowania automatycznego
uint8_t dir = 0;


int main(void){
	init_btn();
	init_servo();
	init_led7s(5);
	init_led();
	init_joy();
//	lcd_init();
	


while(1){
	leds_off;
	
	switch(mode){
		case 0: //sterowanie reczne
			led1_on;
			stop_adc_joy();
			//conf_adc();
			conf_adc();
		
			while( !(ADC1->ISR & ADC_ISR_EOC) ){}
			pwm1 = 8 * ADC1->DR + 500;	//dokladnosc 8 bitowa
			TIM2->CCR1 = T_PWM - pwm1;
			number = pwm1;
		break;
				
				
		case 1: //sterowanie reczne - joystick
			led1_on;
			stop_adc();
			conf_adc_joy();
		
			if( !latch )
			{
				while( !(ADC1->ISR & ADC_ISR_EOC) ){}
				pwm1 = 8 * ADC1->DR + 500;	//dokladnosc 8 bitowa
				TIM2->CCR1 = T_PWM - pwm1;
				number = pwm1;
			}
		break;		
		case 2: //sterowanie automatyczne, max wychylenia
			led2_on;
			TIM2->CCR1   = T_PWM - pwm2;
			if(dir == 0){
			  pwm2 += 25;
			  if(pwm2 >= MAX_PWM)
				  dir = 1; //kierunek ruchu serwa czy dodajemy czy odejmujemy
			}else{
				 pwm2 -= 25;
				 if( pwm2 <= MIN_PWM )
					  dir = 0;
			}
			number = pwm2;
			wait_ms(30); //czas eksperymentalnie w ms, aby serwo sie wyrobilo
				

		break;
			
		case 3: //neutrum
			led3_on;
			number = NEUTRUM;
			TIM2->CCR1 = T_PWM - NEUTRUM;
		break;
		
		case 4: //sterowanie przyciskami
			led4_on;
			TIM2->CCR1 = T_PWM - pwm_btn;
			number = pwm_btn;
		break;
		default:
			mode = 0;
		break;
		
	}
}
	
}

void wait_us(int czas){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->CR1 |= TIM_CR1_ARPE;
	TIM6->PSC |= 48;
	TIM6->ARR |= 1000;
	TIM6->CR1 |= TIM_CR1_CEN;
	while(TIM6->CNT != czas){};
		TIM6->CR1 &= ~TIM_CR1_CEN;
		TIM6->CNT  =0x00;	
}

void wait_ms(int time){
	int t = 0;
	for( ; t < time; t++){
		wait_us(1000);
	}
}
