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

//#include "sram.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>

#define F_CPU 4915200UL			/* Define frequency */
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void test_ADC(){
	volatile char *ext_adc = (char *) 0x1400;
	uint16_t ext_adc_size = 0x400;
	printf("testing ADC");
	
	for (uint16_t i = 0; i < ext_adc_size; i++) {
		_delay_ms(100);
		uint8_t some_value = rand();
		ext_adc[i] = some_value;
	}
	printf("finished testing");
}

void init_parallell_bus(){
	MCUCR = (1 << SRE);
	EMCUCR = (1 << SRW01);
	SFIOR = (1 << XMM2);
}

int main(void)
{
	/*
	SRAM_test();
	test_ADC();
	*/	
	
	/* --- LAB 3 code 
	init_parallell_bus();
	init_UART(BAUD_PRESCALE);
	flush_UART();
	stdout = &mystdout;
	printf("line");
	SRAM_test();
	printf("nytt prog");
	init_clock_adc();
	while(1){
		adc_channels readings = read_channels();
		printf("value ch1");
		printf("The value of myNumber is: %d %d %d %d\n\r ", readings.joystick_left_right, readings.joystick_up_down, readings.slider_left, readings.slider_right);
		_delay_ms(10);
	}
	*/
	
	
	init_parallell_bus();
	init_UART(BAUD_PRESCALE);
	flush_UART();
	stdout = &mystdout;
	oled_init();
	oled_clear_display();
	while(1){
		oled_clear_display();
		_delay_ms(100);
		oled_write_char('A');
		_delay_ms(100);
	}/*
	oled_write_char('A', 0, 0);*/
	

}

