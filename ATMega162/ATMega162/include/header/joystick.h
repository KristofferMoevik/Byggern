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

void calibrate_joystick(){
	int max_value = 255;
	adc_channels adc_values = read_channels();
	int joystick_x_value = adc_channels.joystick_left_right;
	int joystick_y_value = adc_channels.joystick_up_down;
	
	int joystick_error_x = joystick_x_value - max_value;
	int joystick_error_y = joystick_y_value - max_value;
}




#endif /* JOYSTICK_H_ */