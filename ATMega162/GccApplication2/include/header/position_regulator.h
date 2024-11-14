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
	K_p = 1;
	K_i = 100000;
	e_sum = 0;
	frequency = 84000000;
	e_sum_windup = 300;
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
	printf("P: %f, I: %f", P, I);
	/*
	if (output < -100.0){
		output = -100.0;
	}
	if (output > 100.0){
		output = 100.0;
	}
	*/
	output = output;
	return output;
}



#endif /* POSITION_REGULATOR_H_ */