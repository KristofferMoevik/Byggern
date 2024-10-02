/*
 * adc.c
 *
 * Created: 18.09.2024 10:27:20
 *  Author: eveneha
 */ 
#include "adc.h"
#include "../header/addresses.h"

void init_clock_adc() {
    DDRD |= (1 << PD4);
	
	TCCR3A = (1 << COM3A0) | (1 << WGM30) | (1 << WGM31) & ~(1 << COM3A1) & ~(1 << FOC3A);
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30) & ~(1 << CS31) & ~(1 << CS32);
		
	OCR3AH = 0x0;
	OCR3AL = 0x1;
}

adc_channels read_channels(){
	 
	adc_channels adc_readings;
	volatile uint8_t *ext_adc = (uint8_t *) ADDR_BASE + ADDR_OFFSET_ADC; 
	ext_adc[0] = 0;
	adc_readings.joystick_up_down = ext_adc[0];
	adc_readings.joystick_left_right = ext_adc[0];
	adc_readings.slider_left = ext_adc[0];
	adc_readings.slider_right = ext_adc[0];
	return adc_readings;
}


