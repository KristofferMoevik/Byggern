/*
 * check_score.h
 *
 * Created: 06.11.2024 16:17:28
 *  Author: eveneha
 */ 


#ifndef CHECK_SCORE_H_
#define CHECK_SCORE_H_

#include "adc.h"

int score_state;
int sensor_blocked;

int zero_score(){
	score_state = 0;
	sensor_blocked = 0;
}

int poll_score(){
	int adc_value = adc_read();
	if ((adc_value < 1500) && (sensor_blocked == 0)) {
		score_state += 1;
		sensor_blocked = 1;
	}
	if (adc_value > 1500) {
		sensor_blocked = 0;
	}
	return score_state;
}



#endif /* CHECK_SCORE_H_ */