/*
 * tests.h
 *
 * Created: 02.10.2024 11:08:15
 *  Author: eveneha
 */ 
#pragma once
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "oled.h"
#include "external_memory_bus.h"

#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>

#ifndef TESTS_H_
#define TESTS_H_

void test_lab_3(){
	init_external_memory_bus();
	init_UART();
	flush_UART();
	stdout = &uart_out;
	printf("line");
	SRAM_test();
	printf("nytt prog");
	init_clock_adc();
	while(1){
		adc_channels readings = read_channels();
		printf("value ch1");
		printf("The value of myNumber is: %d %d %d %d\n\r ", readings.joystick_left_right, readings.joystick_up_down, readings.slider_left, readings.slider_right);
		_delay_ms(10);
	}
}

void test_lab_4(){
	init_external_memory_bus();
	oled_init();
	oled_clear_screen();
	while(1){
		oled_print_string("pikk", 1);
		_delay_ms(1000);
		oled_clear_screen();
		oled_print_string("pung", 0);
		_delay_ms(1000);
		oled_clear_screen();
		_delay_ms(1000);
	}
}

void adc_test(){
	init_external_memory_bus();
	volatile char *ext_adc = (char *) 0x1400;
	uint16_t ext_adc_size = 0x400;
	printf("testing ADC");
	oled_clear_screen();
	for (uint16_t i = 0; i < ext_adc_size; i++) {
		_delay_ms(100);
		uint8_t some_value = rand();
		ext_adc[i] = some_value;
	}
	printf("finished testing");
}

#endif /* TESTS_H_ */