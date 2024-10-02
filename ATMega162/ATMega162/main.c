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

#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>


int main(void)
{
	test_lab_4();
}

