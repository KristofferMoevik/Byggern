/*
 * joystick.h
 *
 * Created: 02.10.2024 14:33:31
 *  Author: eveneha
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#pragma once
#include "adc.h"

int joystick_error_x;
int joystick_error_y;

/*
enum Direction {
	CENTER = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4	
};

typedef struct
{
	Direction direction;
	int x_value;
	int y_value;
} joystick;
*/

void calibrate_joystick(){
	int max_value = 255;
	int min_value = 0;
	int middle = (max_value - min_value)/2 + min_value;
	adc_channels adc_values = read_channels();
	int joystick_x_value = adc_values.joystick_left_right;
	int joystick_y_value = adc_values.joystick_up_down;
	
	joystick_error_x = joystick_x_value - middle;
	joystick_error_y = joystick_y_value - middle;
}

void send_joystick_can(){
	adc_channels adc_values = read_channels();
	int joystick_x_value = adc_values.joystick_left_right;
	int joystick_y_value = adc_values.joystick_up_down;
	
	can_message msg_send;
	msg_send.id_lower =  0b00000000;
	msg_send.id_higher = 0b00000000;
	msg_send.message_length_bytes = 2;
	msg_send.data[0] = joystick_x_value;
	msg_send.data[1] = joystick_y_value;
	printf("joystick sent x %i , y %i", joystick_x_value, joystick_y_value);
	
	can_send_message(msg_send);
}




#endif /* JOYSTICK_H_ */