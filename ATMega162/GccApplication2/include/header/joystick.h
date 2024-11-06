/*
 * joystick.h
 *
 * Created: 06.11.2024 14:22:25
 *  Author: eveneha
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "can.h"

// auto tune
int joystick_error_x = 0;
int joystick_error_y = 0;
int joystick_max = 255;

float gain_x = 200/(2*(255-188));
int offset_x = -191;

 

int init_joystick(){
	CanMsg msg_recieve;
	
	int success = can_rx(&msg_recieve);
	// can_printmsg(msg_recieve);
	if (!success){
		printf("Failed to recieve message \n\r");
		return 0;
	} else {
		can_printmsg(msg_recieve);
	}
	joystick_error_x = msg_recieve.byte[0];
	joystick_error_y = msg_recieve.byte[1];
	joystick_max = 255;
	gain_x = 200/((joystick_max - joystick_error_x)*2);
	offset_x = -191;
	
	return 1;
}

// return value in range -100 to 100
int read_joystick(){
	CanMsg msg_recieve;	
	int success = can_rx(&msg_recieve);
	printf("\r");
	int x = -1000;
	int y = -1000;
	if (!success){
		printf("Failed to recieve message \n\r");
	} else {
		x = msg_recieve.byte[0];
		y = msg_recieve.byte[1];
		x = gain_x*x + offset_x;
		if (x < -100) {x = -100;}
		if (y < -100) {y = -100;}
		if (x > 100) {x = 100;}
		if (y > 100) {y = 100;}
	}
	return x;
}

#endif /* JOYSTICK_H_ */