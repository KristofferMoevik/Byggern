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
#include "include/header/servo.h"


int main(void)
{
    /* Initialize the SAM system */

    SystemInit();
    init_servo();	
	uart_init(84000000, 9600);
	WDT -> WDT_MR = WDT_MR_WDDIS;
	
	CanInit init;
	init.brp = 41;
	init.phase1 = 6;
	init.phase2 = 5;
	init.propag = 1;
	init.smp = 0;
	init.sjw = 4;
	
	can_init(init, 0);
	
	//set_servo(80);
		
		
		// SJW = 1 
		// BRP 20 
		// PRSEG 2 
		// PS1 7 
		// PS2 6 
	CanMsg msg_recieve;
	msg_recieve.length = 8;
	//can_tx(msg_recieve);
	//test_servo_pin();
	init_servo();
	set_servo(90);
	
	while(1){
		int success = can_rx(&msg_recieve);
		//can_printmsg(msg_recieve);
		if (!success){
			printf("Failed to recieve message \n\r");
		} else {
			can_printmsg(msg_recieve);
		}
	}
}
