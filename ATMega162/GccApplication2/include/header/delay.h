/*
 * delay_us.h
 *
 * Created: 16.10.2024 15:30:48
 *  Author: eveneha
 */ 


#ifndef DELAY_H_
#define DELAY_H_

void _delay_us(uint32_t us) //NB max value is 1597 000us
{
	SysTick->LOAD = 10.5 * us; //MCK = 10.5MHz
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; // Enable SysTick
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); // Wait until Systick timer is finished
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Disable SysTick
}

/* Delays the system for a given number of milli seconds */
void _delay_ms(uint32_t ms)
{
	for(uint32_t i = 0; i<ms; i++){
		_delay_us(1000);
	}
}

/* Setup Timer 0 */
void timer_init(void){
	PMC->PMC_PCER0 |= PMC_PCER0_PID27;
	TC0->TC_WPMR &= ~TC_WPMR_WPEN;
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK3 | TC_CMR_CPCTRG;
	REG_TC0_IER0 |= TC_IER_CPCS;
	
	
	NVIC_EnableIRQ(TC0_IRQn);		// Enable timer counter interrupt
	REG_TC0_CCR0 |= TC_CCR_CLKEN| TC_CCR_SWTRG;		// Enable Timer 0
	REG_TC0_RC0 = 26250;				// counts = 10ms/(32/MCK)

}



#endif /* DELAY_H_ */