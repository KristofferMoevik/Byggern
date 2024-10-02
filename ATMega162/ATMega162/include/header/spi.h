/*
 * spi.h
 *
 * Created: 02.10.2024 15:05:37
 *  Author: eveneha
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_init_clock(){
	DDRD |= (1 << PD4);
	
	TCCR3A = (1 << COM3A0) | (1 << WGM30) | (1 << WGM31) & ~(1 << COM3A1) & ~(1 << FOC3A);
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30) & ~(1 << CS31) & ~(1 << CS32);
		
	OCR3AH = 0x0;
	OCR3AL = 0x1;
}

void SPI_MasterInit(void)
{
	SPI_init_clock();
	/* Set MOSI, SS and SCK output, all others input */
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}



void SPI_MasterTransmit(char cData)
{
	
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

char SPI_MasterRecieve(){
	while(!(SPSR & (1<<SPIF)))
	;
	char data = SPDR;
	return data;
}


#endif /* SPI_H_ */