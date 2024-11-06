/*
 * tests.h
 *
 * Created: 06.11.2024 16:25:33
 *  Author: eveneha
 */ 


#ifndef TESTS_H_
#define TESTS_H_

#include <sam.h>
#include "time.h"
#include "can.h"
#include "delay.h"
#include "servo.h"
#include "joystick.h"
#include "adc.h"
#include "check_score.h"

int test_can(){

	SystemInit();
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
	
	CanMsg msg_recieve;
	
	while(1){
		int success = can_rx(&msg_recieve);
		//can_printmsg(msg_recieve);
		if (!success){
			printf("Failed to recieve message \n\r");
			} else {
			can_printmsg(msg_recieve);
			printf("\r");
		}
	}
}

int test_servo_pwm(){
	/* Initialize the SAM system */

	SystemInit();
	uart_init(84000000, 9600);
	WDT -> WDT_MR = WDT_MR_WDDIS;
	
	init_servo();
	int i = -200;
	while(1){
		set_servo(i);
		printf("tried to set servo to %i \r\n", i);
		_delay_ms(1);
		i++;
		if (i >= 200) {
			i = -200;
		}
	}
}


#endif /* TESTS_H_ */