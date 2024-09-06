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

void init_UART(long BAUD_PRESCALE);

unsigned char recieve_char_UART();

void transmit_char_UART(char letter);

void send_string_UART(char *str);

char* recieve_string_UART();

static FILE mystdout = FDEV_SETUP_STREAM(transmit_char_UART, recieve_char_UART,
_FDEV_SETUP_WRITE);

void test_uart();



#endif /* UART_H_ */