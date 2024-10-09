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
	int i = 0;
	while (1)
	{
		can_send_message(1,i);
		_delay_ms(1000);
		int status = can_read_rx_status();
		printf("dd %i, %i \n\r", status);
		_delay_ms(500);
		int data = can_recieve_message();
		int status2 = can_read_rx_status();
		printf("dd %i, %i \n\r", status2);
		//printf("dd %n \n\r", data);
		++i;
	}
	
	
}

