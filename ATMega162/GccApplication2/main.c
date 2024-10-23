/*
 * GccApplication2.c
 *
 * Created: 16.10.2024 14:04:49
 * Author : eveneha
 */ 



#include <sam.h>
#include "include/header/time.h"
#include "include/header/can.h"
#include "include/header/delay.h"


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
	WDT -> WDT_MR = WDT_MR_WDDIS;
	can_init((CanInit){.brp = 41, .phase1 = 6, .phase2 = 5, .propag = 0, .smp = 0}, 0);
	
		
		
		// SJW = 1 
		// BRP 20 
		// PRSEG 2 
		// PS1 7 
		// PS2 6 
	CanMsg msg_recieve; 
	
	while(1){
		printf("%i", can_rx(&msg_recieve));
		//for (uint8_t ii = 0; ii < msg_recieve.length; ++ii ){
		//	printf(" %i", msg_recieve.dword[ii]);
		//}
		printf(" %i \n\r", msg_recieve.id);
		printf(" %i \n\r", msg_recieve.length);
		printf(" %i \n\r", msg_recieve.dword[0]);
		printf(" %i \n\r", msg_recieve.dword[1]);
	
		
		_delay_ms(1000);
	}
	
}
