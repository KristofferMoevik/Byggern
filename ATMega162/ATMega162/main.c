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

#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>


int main(void)
{
	//test_lab_4();
	//test_lab_3();
	init_external_memory_bus();
	init_UART();
	flush_UART();
	stdout = &uart_out;
	printf("test");
	int fail = can_init();
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
		printf("sent this %i ", i);
		printf(" %i ", i+1);
		printf(" %i ", i+2);
		printf(" %i ", i+3);
		printf(" %i ", i+4);
		printf(" %i ", i+5);
		printf(" %i ", i+6);
		printf(" %i \n\r", i+7);
		
		_delay_ms(100);
		
		uint8_t data[8];
		can_recieve_message(data);
		printf("reci this %i ", data[0]);
		printf(" %i ", data[1]);
		printf(" %i ", data[2]);
		printf(" %i ", data[3]);
		printf(" %i ", data[4]);
		printf(" %i ", data[5]);
		printf(" %i ", data[6]);
		printf(" %i \n\r", data[7]);
		
		printf("\n\r");
		
		_delay_ms(1000);
		
		i = i + 8;
		
	}
	
	
}

