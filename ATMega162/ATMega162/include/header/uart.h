/*
 * uart.h
 *
 * Created: 04.09.2024 16:01:24
 *  Author: alfvv
 */ 


#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>

#ifndef UART_H_
#define UART_H_

#define F_CPU 4915200UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE ((long)(((F_CPU / (USART_BAUDRATE * 16UL))) - 1))

void init_UART();

unsigned char recieve_char_UART();
char* recieve_string_UART();

void transmit_char_UART(char letter);
void send_string_UART(char *str);


static FILE uart_out = FDEV_SETUP_STREAM(transmit_char_UART, recieve_char_UART,
_FDEV_SETUP_WRITE);

void test_uart();


#endif /* UART_H_ */