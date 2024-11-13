/*
 * position_regulator.h
 *
 * Created: 13.11.2024 16:49:45
 *  Author: eveneha
 */ 


#ifndef POSITION_REGULATOR_H_
#define POSITION_REGULATOR_H_

float K_p;
float K_i;
float e_sum;
float frequency;
float e_sum_windup;

void init_position_regulator(){
	K_p = 0.1;
	K_i = 10;
	e_sum = 0;
	frequency = 84000000;
	e_sum_windup = 3000000000;
}

float position_regulator(float position_setpoint, float position){
	float error = position_setpoint - position;
	float P = K_p * error;
	float I = K_i * e_sum/frequency;
	e_sum = e_sum + error;
	
	if (e_sum > e_sum_windup){
		e_sum = e_sum_windup;
	}
	float output = P + I;
	if (output < -100){
		output = -100;
	}
	if (output > 100){
		output = 100;
	}
	
	return output;
}



#endif /* POSITION_REGULATOR_H_ */