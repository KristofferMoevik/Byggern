/*
 * ATMega162.c
 *
 * Created: 04.09.2024 09:43:30
 * Author : Krist
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA |= (1 << PA0); 

	while (1)
	{
		PORTA |= (1 << PA0);
		_delay_ms(10);
		PORTA &= ~(1 << PA0);
		_delay_ms(10);
	}
}

