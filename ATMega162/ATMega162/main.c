/*
 * ATMega162.c
 *
 * Created: 04.09.2024 09:43:30
 * Author : Kristoffer
 */ 

#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "oled.h"
//#include "tests.h"
#include "external_memory_bus.h"
#include "mcp2515.h"
#include "joystick.h"
#include "node_communication.h"
#include "fsm.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>



int main(void){	
	FILE uart_out = FDEV_SETUP_STREAM(transmit_char_UART, recieve_char_UART,
	_FDEV_SETUP_WRITE);
	init_external_memory_bus();
	init_UART();
	//flush_UART();
	//test_oled();
	stdout = &uart_out;
	oled_init();	
	init_clock_adc();
	
	int fail = can_init(MODE_NORMAL);
	if (!fail){
		printf("successfully initializes \n\r");
	}
	
	can_message *recieved_message;
	calibrate_joystick();
	
	
	while (1)
	{
		fsm_main();
	}
	
	
	
	
	printf("test \n\r");
	
	//calibrate_joystick();
	int score = 0;
	while (1) {
		send_commands_to_node_2_can();
		can_recieve_message(recieved_message);
		int score = recieved_message->data[0];
		printf("score: %i \n\r", score);
		//can_print_msg(*recieved_message);
	}
	
}

