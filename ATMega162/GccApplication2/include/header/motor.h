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

int init_motor(){
	// Set phase/dir pin high
	//PIOB->PIO_PER |= PIO_PB12; // enable IO
	PIOB->PIO_OER |= PIO_PB12; // set as output
	PIOB->PIO_PDR |= PIO_PB12;
	PIOB->PIO_ABSR |= PIO_ABSR_P12;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	//PWM->PWM_WPCR &= ~PWM_WPSR_WPHWS2;
	//PWM->PWM_WPCR &= ~PWM_WPSR_WPHWS2;
	
	PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024 | PWM_CMR_CPOL | PWM_CMR_CALG;
	
	float wanted_period = 0.02;
	int default_MCK = 84000000;
	int X = 1024;
	int CPRD = (wanted_period * default_MCK) / (2 * X);
	
	PWM->PWM_CH_NUM[0].PWM_CPRD = CPRD;
	int min_duty = (0.9/20) * CPRD;
	int max_duty = (2.1/20) * CPRD;
	PWM->PWM_CH_NUM[0].PWM_CDTY = min_duty;
	PWM->PWM_ENA |= PWM_ENA_CHID0;
	//PIOB->PIO_PUDR |= PIO_PB12; // disable internal pull-up
	//PIOB->PIO_OWER |= PIO_PB12; // enable output write
	//PIOB->PIO_ODSR |= PIO_PB12; // make pin HIGH
	
	PIOC->PIO_PER |= PIO_PC23; // enable IO
	PIOC->PIO_OER |= PIO_PC23; // set as output
	PIOC->PIO_PUDR |= PIO_PC23; // disable internal pull-up
	PIOC->PIO_OWER |= PIO_PC23; // enable output write
	PIOC->PIO_ODSR |= PIO_PC23; // make pin HIGH
}

int read_encoder_position(){
	int position = TC2->TC_CHANNEL[0].TC_CV;
	return position;
}

int read_encoder_direction(){
	int direction = (TC2->TC_QISR & TC_QISR_DIR) ? 1 : 0;
	return direction;
}

// input speed -100 -> 100
int set_motor_speed(int speed){
	float wanted_period = 0.02;
	int default_MCK = 84000000;
	int X = 1024;
	int CPRD = (wanted_period * default_MCK) / (2 * X);
	PIOC->PIO_ODSR |= PIO_PC23;
	PWM->PWM_CH_NUM[0].PWM_CDTY = CPRD/2;
	/*
	printf("speed: %i", speed);
	if (speed > 0) {
		PIOC->PIO_ODSR |= PIO_PC23;
		int spd = CPRD / (100/speed);
		printf("spd1: %i", spd);
		PWM->PWM_CH_NUM[0].PWM_CDTY = spd;
	}
	if (speed < 0) {
		PIOC->PIO_ODSR &= ~PIO_PC23;
		int spd = CPRD*(-speed/100);
		printf("spd2: %i", spd);
		PWM->PWM_CH_NUM[0].PWM_CDTY = spd;
	}
	if (speed == 0) {
		PIOC->PIO_ODSR |= PIO_PC23;
		PWM->PWM_CH_NUM[0].PWM_CDTY = 0;
	}
	*/
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

int test_motor(){
	int speed = 0;
	int direction = 0;
	
	float wanted_period = 0.02;
	int default_MCK = 84000000;
	int X = 1024;
	int CPRD = (wanted_period * default_MCK) / (2 * X);
	int min_duty = (0.9/20) * CPRD;
	int max_duty = (15/20) * CPRD;
	
	speed = min_duty;
	init_motor();
	while (1){
		printf("speed: %i , direction: %i \n\r", speed, direction);
		set_motor_speed(speed);
		_delay_ms(500);
		if (speed == min_duty) {
			speed = max_duty;
		} else {
			speed = min_duty;
		}
		
		if (direction == 0) {
			direction = 1;
		} else {
			direction = 0;
		}
	}
}


#endif /* MOTOR_H_ */