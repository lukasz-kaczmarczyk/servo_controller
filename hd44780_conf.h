/*
  konfiguracja pinów wyswietlacza hd44780
	
	podlaczenie:
	RW PC10
	RS PC11
	E PC12
	D4 PB3
	D5 PB4
	D6 PB5
	D7 PB6
	
	potencjometr 1k szeregowo z 460R do V0
*/

#ifndef HD44780_CONF_H_
#define HD44780_CONF_H_

#include <stm32f0xx.h>

//RW PC4
#define RW_PIN (1 << 4)
#define RW_AHBENR RCC_AHBENR_GPIOCEN
#define RW_GPIO GPIOC
#define RW_OUT GPIO_MODER_MODER4_0
#define rw_on ( RW_GPIO->ODR |= RW_PIN )
#define rw_off ( RW_GPIO->ODR &= ~RW_PIN )

//RS PC5
#define RS_PIN (1 << 5)
#define RS_AHBENR RCC_AHBENR_GPIOCEN
#define RS_GPIO GPIOC
#define RS_OUT GPIO_MODER_MODER5_0
#define rs_on ( RS_GPIO->ODR |= RS_PIN )
#define rs_off ( RS_GPIO->ODR &= ~RS_PIN )

//E PB12
#define E_PIN (1 << 12)
#define E_AHBENR RCC_AHBENR_GPIOBEN
#define E_GPIO GPIOB
#define E_OUT GPIO_MODER_MODER12_0
#define e_on ( E_GPIO->ODR |= E_PIN )
#define e_off ( E_GPIO->ODR &= ~E_PIN )

//D4 PA7
#define D4_PIN (1 << 7)
#define D4_AHBENR RCC_AHBENR_GPIOAEN
#define D4_GPIO GPIOA
#define D4_OUT GPIO_MODER_MODER7_0
#define d4_on ( D4_GPIO->ODR |= D4_PIN )
#define d4_off ( D4_GPIO->ODR &= ~D4_PIN )

//D5 PA6
#define D5_PIN (1 << 6)
#define D5_AHBENR RCC_AHBENR_GPIOAEN
#define D5_GPIO GPIOA
#define D5_OUT GPIO_MODER_MODER6_0
#define d5_on ( D5_GPIO->ODR |= D5_PIN )
#define d5_off ( D5_GPIO->ODR &= ~D5_PIN )

//D6 PA5
#define D6_PIN (1 << 5)
#define D6_AHBENR RCC_AHBENR_GPIOAEN
#define D6_GPIO GPIOA
#define D6_OUT GPIO_MODER_MODER5_0
#define d6_on ( D6_GPIO->ODR |= D6_PIN )
#define d6_off ( D6_GPIO->ODR &= ~D6_PIN )

//D7 PA4
#define D7_PIN (1 << 4)
#define D7_AHBENR RCC_AHBENR_GPIOAEN
#define D7_GPIO GPIOA
#define D7_OUT GPIO_MODER_MODER4_0
#define d7_on ( D7_GPIO->ODR |= D7_PIN )
#define d7_off ( D7_GPIO->ODR &= ~D7_PIN )

//definition hd44780 parameters
#define DL_4B 0x20
#define DL_8B 0x30
#define N_2L  0x28
#define N_1L  0x20
#define F_5_7  0x20  
#define F_5_10 0x24

//entry mode
#define DEC_CURSOR_POS  0x04
#define INC_CURSOR_POS  0x06
#define NO_DISPLAY_SHIFT  0x04
#define DISPLAY_SHIFT  0x05

//display on/off control
#define DISPLAY_OFF 0x08
#define DISPLAY_ON 0x0C
#define CURSOR_OFF 0x08
#define CURSOR_ON  0x0A
#define CURSOR_BLINK_OFF 0x08
#define CURSOR_BLINK_ON 0x09

//cursor/ display shift
#define MOVE_CURSOR				0x10
#define SHIFT_DISPLAY			0x18
#define SHIFT_LEFT				0x10
#define SHIFT_RIGHT				0x14


#define CLS  0x01
#define CURSOR_HOME  0x02

//cursor position
#define LINE_1			0x80
#define LINE_2			0xC0

/*
char bell[8] = {
	0x04,
	0x0E,
	0x0E,
	0x0E,
	0x1F,
	0x00,
	0x04,
	0x00
};


//litera a
//http://old.piko.avx.pl/index.php?k=mk51&p=wlcd
char lit1[8] = {
	0x00,
	0x00,
	0x0E,
	0x01,
	0x0F,
	0x11,
	0x0F,
	0x04
};

*/


#endif

