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
	while (1)
	{
		char address = MCP_RXF0SIDH;
		char d = can_read(address);
		printf("%d \n", d);
		
		_delay_ms(500); 
		char data = 1;
		can_write(address, data);
		_delay_ms(500);
		d = can_read(address);
		printf("%d \n", d);
		
		_delay_ms(500);
		data = 0;
		can_write(address, data);
		_delay_ms(500);
		
	}
	
	
}

