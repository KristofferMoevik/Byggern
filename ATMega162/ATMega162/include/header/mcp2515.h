/*
 * mcp2515.h
 *
 * Created: 02.10.2024 15:17:01
 *  Author: eveneha
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_

#include "spi.h"

void can_init(){
	SPI_MasterInit();
}

void can_reset(){
	char reset_command = 0b11000000; // From table 12-1
	PORTB |= (0<<PB4);
	SPI_MasterTransmit(reset_command);
	PORTB &= (1<<PB4);

}

char can_read(){
	PORTB |= (0<<PB4);
	SPI_MasterTransmit(0b00000011);
	SPI_MasterTransmit(0b00000011);
	char data = SPI_MasterRecieve();
	PORTB &= (1<<PB4);
	return data;
}

void can_write(char instruction, char address, char data){
	PORTB |= (0<<PB4);
	SPI_MasterTransmit(instruction):
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	PORTB &= (1<<PB4);	
}







#endif /* MCP2515_H_ */