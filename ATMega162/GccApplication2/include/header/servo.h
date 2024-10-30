/*
 * servo.h
 *
 * Created: 30.10.2024 13:14:09
 *  Author: eveneha
 */ 

#include "sam.h"
#ifndef SERVO_H_
#define SERVO_H_

void init_servo(){
	PIOB->PIO_PER |= (1 << 13); // enable IO
	PIOB->PIO_OER |= (1 << 13); // set as output
	PIOB->PIO_PUDR |= (1 << 13); // disable internal pull-up
	PIOB->PIO_OWER |= (1 << 13); // enable output write
	
	PMC->PMC_PCER0 |= PMC_PCER0_PID13;
	PMC->PMC_SCER = PMC_SCER_PCK0 | PMC_SCER_PCK1 | PMC_SCER_PCK2;
	PWM->PWM_WPCR &= ~PIO_WPMR_WPEN;
	
	REG_PWM_CMR5 = PWM_CMR_CPRE_MCK_DIV_1024 | PWM_CMR_CPOL; 
	
	// min = 74 
	// max = 172 valus
	REG_PWM_CPRD5 = 1640;			//CPRD = 20ms * 84MHz/1024
	REG_PWM_CDTY5 = 123;			//CPRY = 1.5ms * 84MHz/1024 
	
	REG_PWM_ENA = PWM_ENA_CHID5;
	
	
}

void test_servo_pin(){
	
	uint64_t min_pulse = msecs(0.9);
	uint64_t max_pulse = msecs(2.1);
	uint64_t pwm_period = msecs(20);
	/* Replace with your application code */
	while (1)
	{
		PIOB->PIO_ODSR |= (1 << 13); // make pin HIGH
		time_spinFor(100000);
		PIOB->PIO_ODSR &= ~(1 << 13); // make pin LOW
		time_spinFor(100000000);
		printf("Kristoffer liker å forske på havet \n\r");
	}
}

// position setpoint range -100 to 100
void set_servo(uint64_t position_setpoint){
	uint64_t min_pulse = 74;
	uint64_t max_pulse = 172;
	uint64_t pwm_period = msecs(20);
	
	uint64_t zero = ((max_pulse - min_pulse) / 2) + min_pulse;
	uint64_t gain = (max_pulse - zero) / 100;
	
	uint64_t pulse_width = position_setpoint * gain +zero; 
	
	REG_PWM_CDTY5 = 90;
	
}



#endif /* SERVO_H_ */