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
#include "tests.h"
#include "mcp2515.h"
#include "joystick.h"
#include "node_communication.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>



int main(void){	
	
	init_external_memory_bus();
	init_UART();
	flush_UART();
	init_clock_adc();
	stdout = &uart_out;
	printf("test \n\r");
	int fail = can_init(MODE_NORMAL);
	if (!fail){
		printf("successfully initializes \n\r");
	}
	
	can_message *recieved_message;
	calibrate_joystick();
	while (1) {
		send_commands_to_node_2_can();
		can_recieve_message(recieved_message);
		//can_print_msg(*recieved_message);
	}
}

