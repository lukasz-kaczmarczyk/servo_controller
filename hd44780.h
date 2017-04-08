/*
  sterowanie wyswietlaczem opartym o sterownik hd44780
	
	ver 2:
	tworzenie wlasnych znaków
	tablica znaków w pliku conf.h

*/

#ifndef HD44780_H_
#define HD44780_H_

#include <stm32f0xx.h>


void lcd_init(void);
//void bit4_disp(void);
void lcd_disp_A(void);
void lcd_disp_B(void);
void lcd_disp_C(void);
void lcd_disp_D(void);
void lcd_disp_napis( char *napis );
void lcd_cursor_line(uint8_t r);
void lcd_cursor_position( uint8_t l, uint8_t r );
void lcd_disp_data(char data);
void lcd_lcd_clear(void);



#endif

