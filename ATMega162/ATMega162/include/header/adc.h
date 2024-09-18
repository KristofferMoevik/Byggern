/*
 * adc.h
 *
 * Created: 18.09.2024 10:27:07
 *  Author: eveneha
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#include "uart.h"
#include <avr/delay.h>

typedef struct
{
	int joystick_up_down;
	int joystick_left_right;
	int slider_left;
	int slider_right;
} adc_channels;


//volatile char *ADC_MEMORY_ADDRESS = (char *) 0x1400;


void init_clock_adc();

void adc_init();

adc_channels read_channels();


#endif /* ADC_H_ */