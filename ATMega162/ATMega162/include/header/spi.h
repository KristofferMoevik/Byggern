/*
 * spi.h
 *
 * Created: 02.10.2024 15:05:37
 *  Author: eveneha
 */ 


#ifndef SPI_H_
#define SPI_H_


void SPI_MasterInit(void)
{
	/* Set MOSI, SS and SCK output, all others input */
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}



void SPI_MasterTransmit(char data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

char SPI_MasterRecieve(){
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)))
	;
	char data = SPDR;
	return data;
}


#endif /* SPI_H_ */