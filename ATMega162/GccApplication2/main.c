/*
 * GccApplication2.c
 *
 * Created: 16.10.2024 14:04:49
 * Author : eveneha
 */ 



#include <sam.h>
#include "include/header/time.h"
#include "include/header/can.h"


void test_servi_pin(){
	PIOB->PIO_PER |= (1 << 13); // enable IO
	PIOB->PIO_OER |= (1 << 13); // set as output
	PIOB->PIO_PUDR |= (1 << 13); // disable internal pull-up
	PIOB->PIO_OWER |= (1 << 13); // enable output write
	
    /* Replace with your application code */
    while (1) 
    {	
		PIOB->PIO_ODSR |= (1 << 13); // make pin HIGH
		time_spinFor(100000000);
		PIOB->PIO_ODSR &= ~(1 << 13); // make pin LOW
		time_spinFor(100000000);
		printf("Kristoffer liker å forske på havet \n\r");
    }
}


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	uart_init(84000000, 9600);
	can_init((CanInit){.brp = 3, .phase1 = 5, .phase2 = 1, .propag = 6}, 0);
	while(1){
		CanMsg m;
		uint8_t can_rx(CanMsg* m);
		can_printmsg(m);
		printf("\n\r");
	}
	
}
