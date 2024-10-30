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

#include <stdbool.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>



int main(void)
{	
	
	init_external_memory_bus();
	init_UART();
	flush_UART();
	init_clock_adc();
	stdout = &uart_out;
	printf("test");
	int fail = can_init(MODE_NORMAL);
	if (!fail){
		printf("successfully initializes");
	}
	
	char cnf1 = can_read(MCP_CNF1);
	char cnf2 = can_read(MCP_CNF2);
	char cnf3 = can_read(MCP_CNF3);
	
	printf("cnf1: %d", cnf1);
	printf("cnf2: %d", cnf2);
	printf("cnf3: %d", cnf3);
	
	
	can_message msg_send;
	msg_send.id_lower =  0b10000000;
	msg_send.id_higher = 0b00000000;
	msg_send.message_length_bytes = 8;
	msg_send.data[0] = 0;
	msg_send.data[1] = 2;
	msg_send.data[2] = 2;
	msg_send.data[3] = 3;
	msg_send.data[4] = 4;
	msg_send.data[5] = 5;
	msg_send.data[6] = 6;
	msg_send.data[7] = 7;
	
	
	calibrate_joystick();
	while(1){
		send_joystick_can();
		_delay_ms(10);
	}
	
	/*
	can_message msg_send;
	msg_send.id_lower =  0b10000000;
	msg_send.id_higher = 0b00000000;
	msg_send.message_length_bytes = 8;
	uint8_t i = 0;
	msg_send.data[0] = 0;
	msg_send.data[1] = 2;
	msg_send.data[2] = 2;
	msg_send.data[3] = 3;
	msg_send.data[4] = 4;
	msg_send.data[5] = 5;
	msg_send.data[6] = 6;
	msg_send.data[7] = 7;
	
	can_send_message(msg_send);
	printf("%i, hei hei hei ", msg_send.message_length_bytes);
	
	
	while(1) {
		
		msg_send.data[0] = i;
		msg_send.data[1] = i+1;
		msg_send.data[2] = i+2;
		msg_send.data[3] = i+3;
		msg_send.data[4] = i+4;
		msg_send.data[5] = i+5;
		msg_send.data[6] = i+6;
		msg_send.data[7] = i+7;
		can_send_message(msg_send);
		printf("sent: ");
		for (uint8_t ii = 0; ii < msg_send.message_length_bytes; ++ii ){
			printf(" %i", msg_send.data[ii]);
		}
		i++; 
		printf("\n ID: %i \n\r", msg_send.id_lower); 
		//printf(" %i \n\r", msg_send.id_higher);
		printf("Length: %i \n\r", msg_send.message_length_bytes);
		printf("Data[0]: %i \n\r", msg_send.data[0]);  
		
		
		_delay_ms(1000);
		char tx0 = can_read(MCP_TXB0CTRL);
		printf("%i hallo i luka! ", tx0); 
		
		tx0 = can_read(MCP_CANINTF);
		
		printf("%i hallo ", tx0);
	
	}
	can_message msg_recieve;
	can_recieve_message(&msg_recieve);
	*/
	
	
}

