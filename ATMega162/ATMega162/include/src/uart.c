/*
 * uart.c
 *
 * Created: 04.09.2024 16:01:16
 *  Author: alfvv
 */ 

#include "uart.h"


void init_UART(long BAUD_PRESCALE){
	/* Set baud rate */
	UBRR0H = (unsigned char)(BAUD_PRESCALE>>8); //Baudrate reg
	UBRR0L = (unsigned char)BAUD_PRESCALE; //Baudrate reg
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

void flush_UART( void )
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

unsigned char recieve_char_UART(){
	while ( !( UCSR0A & (1 << RXC0) ) );/* Wait till data is received */
	return(UDR0);			/* Return the byte*/
}

void transmit_char_UART(char letter){
	while (! (UCSR0A & (1<<UDRE0)));	/* Wait for empty transmit buffer*/
	UDR0 = letter;
}


void test_uart(long BAUD_PRESCALE){
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


//void send_string_UART(char *str);

//char* recieve_string_UART();	