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
#include "mcp2515.h"


#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>
#include <stdbool.h>


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

void test_lab_5(){
	init_external_memory_bus();
	init_UART();
	flush_UART();
	stdout = &uart_out;
	printf("test");
	int fail = can_init(MODE_LOOPBACK);
	if (!fail){
		printf("successfully initializes");
	}
	uint8_t i = 0;
	while (1)
	{
		can_message msg_send;
		msg_send.id_lower = 0b00100000;
		msg_send.id_higher = 0b00000000;
		msg_send.message_length_bytes = 8;
		
		msg_send.data[0] = i;
		msg_send.data[1] = i+1;
		msg_send.data[2] = i+2;
		msg_send.data[3] = i+3;
		msg_send.data[4] = i+4;
		msg_send.data[5] = i+5;
		msg_send.data[6] = i+6;
		msg_send.data[7] = i+7;
		can_send_message(msg_send);
				
		can_message *recieved_msg;
		can_recieve_message(recieved_msg);
		
		bool messages_are_the_same = true;
		
		for (uint8_t ii = 0; ii < msg_send.message_length_bytes; ++ii ){
			if (!(msg_send.data[ii] == recieved_msg->data[ii])){
				messages_are_the_same = false;
				break;
			}
		}
		
		if (messages_are_the_same){
			printf("messages are the same:)");
		} else {
			printf("!!! messages are not the same:(((");
		}
		
		_delay_ms(1000);
		
		i = i + 8;
		
		if (i > 100){
			break;
		}
		
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