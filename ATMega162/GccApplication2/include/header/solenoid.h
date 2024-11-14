/*
 * solenoid.h
 *
 * Created: 06.11.2024 16:44:51
 *  Author: eveneha
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

#include "sam.h"

int init_solenoid() {
	// Set phase/dir pin high
	PIOB->PIO_PER |= PIO_PB25; // enable IO
	PIOB->PIO_OER |= PIO_PB25; // set as output
	//PIOB->PIO_PUDR |= PIO_PB25; // disable internal pull-up
	PIOB->PIO_OWER |= PIO_PB25; // enable output write
	PIOB->PIO_ODSR |= PIO_PB25; // make pin HIGH
}

int test_solenoid(){
	while (1)
	{
		PIOB->PIO_ODSR |= PIO_PB25; // make pin HIGH
		_delay_ms(1000);
		PIOB->PIO_ODSR &= ~PIO_PB25;
		_delay_ms(1000);
	}
}

int shoot_solenoid(int shoot){
	if (shoot)
	{
		PIOB->PIO_ODSR &= ~PIO_PB25;
	}
	else {
		PIOB->PIO_ODSR |= PIO_PB25;
	}
}


#endif /* SOLENOID_H_ */