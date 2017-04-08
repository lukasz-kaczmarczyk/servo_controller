#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#include <stm32f0xx.h>

//extern uint8_t latch;
void conf_adc_joy(void);
void stop_adc_joy(void);
void init_joy(void);
#endif

