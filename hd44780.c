#include "hd44780.h"
#include "hd44780_conf.h"

static void lcd_sendHalf(uint8_t data);
static void init_disp(void);
static void write_cmd(uint8_t cmd);
static void wait_us(short time);
static void wait_ms(short time);
static void send_data( char data );
static void lcd_build_bell(void);
static void build_sign(char addr, char sign[]);

void lcd_init(void){
	//init RW
	RCC->AHBENR |= RW_AHBENR;
	RW_GPIO->MODER |= RW_OUT;
	
		//init RS
	RCC->AHBENR |= RS_AHBENR;
	RS_GPIO->MODER |= RS_OUT;
	rs_off;
	
	//init E
	RCC->AHBENR |= E_AHBENR;
	E_GPIO->MODER |= E_OUT;
	e_off;
	
	//init D4
	RCC->AHBENR |= D4_AHBENR;
	D4_GPIO->MODER |= D4_OUT;
	d4_off;
	
	//init D5
	RCC->AHBENR |= D5_AHBENR;
	D5_GPIO->MODER |= D5_OUT;
	d5_off;
	
	//init D6
	RCC->AHBENR |= D6_AHBENR;
	D6_GPIO->MODER |= D6_OUT;
	d6_off;
	
	//init D7
	RCC->AHBENR |= D7_AHBENR;
	D7_GPIO->MODER |= D7_OUT;
	d7_off;
	
	init_disp();
}

void lcd_disp_A(){
	rs_on;
	e_on;
	lcd_sendHalf(0x04);
	e_off;
	e_on;
	lcd_sendHalf(0x01);
	e_off;
	wait_ms(2);
	rs_off;
}

void lcd_disp_B(){
	rs_on;
	e_on;
	lcd_sendHalf(0x04);
	e_off;
	e_on;
	lcd_sendHalf(0x02);
	e_off;
	wait_ms(2);
	rs_off;
}

void lcd_disp_C(){
	rs_on;
	e_on;
	lcd_sendHalf(0x04);
	e_off;
	e_on;
	lcd_sendHalf(0x03);
	e_off;
	wait_ms(2);
	rs_off;
}

void lcd_disp_D(){
	rs_on;
	e_on;
	lcd_sendHalf('D' >> 4);
	e_off;
	e_on;
	lcd_sendHalf('D');
	e_off;
	wait_ms(2);
	rs_off;
}

void lcd_disp_data( char data ){
	rs_on;
	e_on;
	lcd_sendHalf(data >> 4);
	e_off;
	//wait_us(200);
	e_on;
	lcd_sendHalf(data);
	e_off;
	wait_us(120);
	rs_off;
}



void lcd_disp_napis( char *napis ){
	while( *napis )
		lcd_disp_data(*napis++);
}

void lcd_cursor_line(uint8_t r){
	uint8_t command;
	if( r == 1 ){
		command = 0x80;
	}
	if( r == 2 ){
		command = 0x40 | 0x80;
	}
	
	rs_off;
	e_on;
	lcd_sendHalf(command >> 4);
	e_off;
	e_on;
	lcd_sendHalf( command );
	e_off;
	wait_us(100);
}

void lcd_clear(){
	write_cmd(CLS);
}




void lcd_cursor_position( uint8_t l, uint8_t r ){
	if(l == 1)
		write_cmd(LINE_1 | r);
		//tmp = LINE_1;
	if(l == 2)
		//tmp = LINE_2;
	  write_cmd(LINE_2 | r);
	wait_us(100);
}
//static function-----------------------------------------
static void init_disp(void){
	rs_off; rw_off; e_off;
	d4_off; d5_off; d6_off, d7_off;
	wait_ms(10);
	
	e_on;
  lcd_sendHalf(0x03);
	e_off;
	wait_ms(5); //wiecej niz 4.1ms
	
	e_on;
	lcd_sendHalf(0x03);
	e_off;
	wait_us(110); //wiecej niz 100us
	
	e_on;
  lcd_sendHalf(0x03);
	e_off;
	wait_us(110); //wiecej niz 100us
	
	e_on;
	lcd_sendHalf(0x02);
	e_off;
	wait_us(110);
	/////////////////////////////////////
 
  lcd_clear();
  //4 bit, 2 lines, 5x7
	write_cmd(DL_4B | N_2L | F_5_10);
	
	//zachowanie kursora
	write_cmd(INC_CURSOR_POS | NO_DISPLAY_SHIFT);
	
	//display on/off control
	write_cmd(DISPLAY_ON | CURSOR_ON | CURSOR_BLINK_ON);
	
	write_cmd(MOVE_CURSOR | SHIFT_RIGHT);
	
//	build_sign(0,lit1);
	
}

static void lcd_sendHalf(uint8_t data){
	
	d4_off; d5_off; d6_off; d7_off;
	if( data & (1 << 0) )
		d4_on;
	if( data & (1 << 1) )
		d5_on;
	if( data & (1 << 2) )
		d6_on;
	if( data & (1 << 3) )
		d7_on;
}

static void write_cmd(uint8_t cmd){
	rs_off;
	e_on;
	lcd_sendHalf( cmd >> 4 );
	e_off;
	//wait();
	e_on;
	lcd_sendHalf( cmd );
	e_off;
	wait_us(100);
}

static void wait_us(short time){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 48;
	TIM6->ARR = time;
	TIM6->CR1 |= TIM_CR1_ARPE; //??
	TIM6->CR1 |= TIM_CR1_OPM;
	TIM6->CR1 |= TIM_CR1_CEN;
	
	while(TIM6->CR1 & TIM_CR1_CEN){}
	
}


static void wait_ms(short time){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 0xBB80;
	TIM6->ARR = time;
	//TIM6->CR1 |= TIM_CR1_ARPE; //??

	TIM6->CR1 |= TIM_CR1_CEN | TIM_CR1_OPM;
	
	while(!TIM6->SR){}
	TIM6->SR = 0x00;
}

static void send_data( char data ){
	rs_on;
	e_on;
	lcd_sendHalf(data >> 4);
	e_off;
	//wait_us(200);
	e_on;
	lcd_sendHalf(data);
	e_off;
	wait_us(100);
	rs_off;
}
static void lcd_build_bell(){
	write_cmd(0x40);
	send_data(0x04);
	send_data(0x0E);
	send_data(0x0E);
	send_data(0x0E);
	send_data(0x1F);
	send_data(0x00);
	send_data(0x04);
	send_data(0x00);
	write_cmd(LINE_1);
	
	
}
static void build_sign(char addr, char sign[]){
	char tmp = 0;
	write_cmd(0x40 | addr);
	for(tmp = 0; tmp < 8; ++tmp){
		send_data(sign[tmp]);
	}
}

//end hd44780.c




