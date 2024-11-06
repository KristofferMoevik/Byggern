/*
 * adc.h
 *
 * Created: 06.11.2024 15:34:42
 *  Author: eveneha
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "sam.h"

int init_adc(){
	PMC->PMC_PCR |= (PMC_PCR_EN) | (0b100101);
	PMC->PMC_PCER1 |=  PMC_PCER1_PID37;
	
	ADC->ADC_MR |= ADC_MR_FREERUN_ON;
	ADC->ADC_CHER |= ADC_CHER_CH0;
	
	ADC->ADC_CR |= ADC_CR_START;

}

	
int adc_read(){
	return ADC->ADC_CDR[0];
}



#endif /* ADC_H_ */