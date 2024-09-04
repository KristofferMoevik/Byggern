/*
 * ATMega162.c
 *
 * Created: 04.09.2024 09:43:30
 * Author : Krist
 */ 

#include "uart.h"
#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 4915200UL			/* Define frequency */
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


int main(void)
{
	init_UART(BAUD_PRESCALE);
	flush_UART();
	
	char c;
	while(1)
	{
		c=recieve_char_UART();
		transmit_char_UART(c);
		stdout = &mystdout;
		printf("Hello, world!\n");
	}
}

