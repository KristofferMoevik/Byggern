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

#include <stdbool.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>


int main(void)
{
	init_external_memory_bus();
	init_UART();
	flush_UART();
	stdout = &uart_out;
	printf("test");
	int fail = can_init(MODE_NORMAL);
	if (!fail){
		printf("successfully initializes");
	}
	init_UART();

	while(1){
		can_message msg_send;
		msg_send.id_lower = 0b00100000;
		msg_send.id_higher = 0b00000000;
		msg_send.message_length_bytes = 8;
		uint8_t i = 0;
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
		printf(" \n\r");
		_delay_ms(1000);
	}
	
}

