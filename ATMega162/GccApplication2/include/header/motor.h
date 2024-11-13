/*
 * motor.h
 *
 * Created: 13.11.2024 09:25:16
 *  Author: eveneha
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "sam.h"  // Device header

int init_encoder(){
	//Enable inputs todo
	PIOC->PIO_PER |= PIO_PC25;
	PIOC->PIO_PER |= PIO_PC26;

	PIOC->PIO_PDR |= PIO_PC25;
	PIOC->PIO_PDR |= PIO_PC26;
	
	PIOC->PIO_OER |= PIO_PC25;
	PIOC->PIO_OER |= PIO_PC26;
	
	PIOC->PIO_ABSR |= PIO_ABSR_P25;
	PIOC->PIO_ABSR |= PIO_ABSR_P26;
	
	// Enable clock
	//TC2->TC_CHANNEL[0]
	PMC->PMC_PCER1 |= PMC_PCER1_PID33;
	PMC->PMC_PCER0 |= PMC_PCER0_PID29;
	
	PMC->PMC_PCR |= PMC_PCR_EN | 0b11101;
	
	//TC2->TC_CHANNEL[0].
	TC2->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_XC0;
	TC2->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN | TC_CCR_SWTRG; 
	TC2->TC_BMR |= TC_BMR_QDEN | TC_BMR_POSEN; //| TC_BMR_TC1XC1S_TIOA0 | TC_BMR_TC0XC0S_TIOA1 // kAN VÆRE FEIL
}

int read_encoder_position(){
	int position = TC2->TC_CHANNEL[0].TC_CV;
	return position;
}

int read_encoder_direction(){
	int direction = (TC2->TC_QISR & TC_QISR_DIR) ? 1 : 0;
	return direction;
}

int test_encoder(){
	init_encoder();
	while (1){
		int pos = read_encoder_position();
		int dir = read_encoder_direction();
		printf("pos: %i, dir: %i \n\r", pos, dir);
		_delay_ms(100);
	}
}


#endif /* MOTOR_H_ */