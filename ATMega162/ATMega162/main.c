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
	can_init();
	
	char data = can_read();
	printf("%data", data);
	
}

