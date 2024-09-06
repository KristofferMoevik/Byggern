/*
 * ATMega162.c
 *
 * Created: 04.09.2024 09:43:30
 * Author : Krist
 */ 

#include "uart.h"
#include "sram.h"

//#include "sram.h"
#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 4915200UL			/* Define frequency */
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void test_ADC(){
	volatile char *ext_adc = (char *) 0x1400;
	uint16_t ext_adc_size = 0x400;
	while(1)
	{
		for (uint16_t i = 0; i < ext_adc_size; i++) {
			uint8_t some_value = rand();
			ext_adc[i] = some_value;
		}
	}
	
}

int main(void)
{

	MCUCR |= (1 << SRE);  // Enable external SRAM
	init_UART(BAUD_PRESCALE);
	flush_UART();
	stdout = &mystdout;
	printf("allahu akbar");
	SRAM_test();
	test_ADC();	
}

