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
	// PIOB->PIO_PER |= PIO_PB13; // enable IO
	PIOB->PIO_OER |= PIO_PB13; // set as output
	PIOB->PIO_PDR |= PIO_PB13;
	// Assign peripheral function B to pin PB13 with is PWM
	PIOB->PIO_ABSR |= PIO_ABSR_P13;
	
	PMC->PMC_PCER1 |= (1 << 4);
	
	
	//PMC->PMC_SCER = PMC_SCER_PCK0 | PMC_SCER_PCK1 | PMC_SCER_PCK2;
	PWM->PWM_WPCR &= ~PWM_WPSR_WPHWS2;
	PWM->PWM_WPCR &= ~PWM_WPSR_WPSWS2;	
	PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024 | PWM_CMR_CPOL | PWM_CMR_CALG;
	float wanted_period = 0.02;
	int default_MCK = 84000000;
	int X = 1024;
	int CPRD = (wanted_period * default_MCK) / (2 * X);
	
	PWM->PWM_CH_NUM[1].PWM_CPRD = CPRD; // Side 1048 ;
	int min_duty = (0.9/20) * CPRD;
	int max_duty = (2.1/20) * CPRD;
	PWM->PWM_CH_NUM[1].PWM_CDTY = min_duty;
	PWM->PWM_ENA |= PWM_ENA_CHID1;
	
	// Set phase/dir pin high
	PIOB->PIO_PER |= PIO_PB12; // enable IO
	PIOB->PIO_OER |= PIO_PB12; // set as output
	PIOB->PIO_PUDR |= PIO_PB12; // disable internal pull-up
	PIOB->PIO_OWER |= PIO_PB12; // enable output write
	PIOB->PIO_ODSR |= PIO_PB12; // make pin HIGH

	// PIO_PSR
	// PIO_SODR
	
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
void set_servo(int position_setpoint){
	float wanted_period = 0.02;
	int default_MCK = 84000000;
	int X = 1024;
	int CPRD = (wanted_period * default_MCK) / (2 * X);
	int min_duty = (0.9/20) * CPRD;
	int max_duty = (2.1/20) * CPRD;
	
	int mapped_setpoint = ( ( ( (1.2/200)*(position_setpoint - 100) ) + 2.1 ) / 20 ) * CPRD;
	
	if ((mapped_setpoint <= max_duty) && (mapped_setpoint >= min_duty)){
		PWM->PWM_CH_NUM[1].PWM_CDTY = mapped_setpoint;
	} else {
		if (mapped_setpoint >= max_duty)
		{
			PWM->PWM_CH_NUM[1].PWM_CDTY = max_duty;
		}
		if (mapped_setpoint <= min_duty)
		{
			PWM->PWM_CH_NUM[1].PWM_CDTY = min_duty;
		}
	}
}



#endif /* SERVO_H_ */