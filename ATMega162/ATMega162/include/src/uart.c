/*
 * uart.c
 *
 * Created: 04.09.2024 16:01:16
 *  Author: alfvv
 */ 

#include "uart.h"


void init_UART(){

	UBRR0H = (unsigned char)(BAUD_PRESCALE>>8); //Baudrate reg
	UBRR0L = (unsigned char)BAUD_PRESCALE; //Baudrate reg
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

void flush_UART( void )
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

unsigned char recieve_char_UART(){
	while ( !( UCSR0A & (1 << RXC0) ) );
	return(UDR0);
}

void transmit_char_UART(char letter){
	while (! (UCSR0A & (1<<UDRE0))){};
	UDR0 = letter;
}


void test_uart(){
	init_UART();
	flush_UART();
	
	char c;
	while(1)
	{
		c=recieve_char_UART();
		transmit_char_UART(c);
		//stdout = &uart_out;
		printf("Hello, world!\n");
	}
	
}
	