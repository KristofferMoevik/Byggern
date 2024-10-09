/*
 * mcp2515.h
 *
 * Created: 02.10.2024 15:17:01
 *  Author: eveneha
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_

#include "spi.h"

/*
This file contains constants that are specific to the MCP2515.

Version     Date        Description
----------------------------------------------------------------------
v1.00       2003/12/11  Initial release

Copyright 2003 Kimberly Otten Software Consulting
*/

// Define MCP2515 register addresses

#define MCP_RXF0SIDH	0x00
#define MCP_RXF0SIDL	0x01
#define MCP_RXF0EID8	0x02
#define MCP_RXF0EID0	0x03
#define MCP_RXF1SIDH	0x04
#define MCP_RXF1SIDL	0x05
#define MCP_RXF1EID8	0x06
#define MCP_RXF1EID0	0x07
#define MCP_RXF2SIDH	0x08
#define MCP_RXF2SIDL	0x09
#define MCP_RXF2EID8	0x0A
#define MCP_RXF2EID0	0x0B
#define MCP_CANSTAT		0x0E
#define MCP_CANCTRL		0x0F
#define MCP_RXF3SIDH	0x10
#define MCP_RXF3SIDL	0x11
#define MCP_RXF3EID8	0x12
#define MCP_RXF3EID0	0x13
#define MCP_RXF4SIDH	0x14
#define MCP_RXF4SIDL	0x15
#define MCP_RXF4EID8	0x16
#define MCP_RXF4EID0	0x17
#define MCP_RXF5SIDH	0x18
#define MCP_RXF5SIDL	0x19
#define MCP_RXF5EID8	0x1A
#define MCP_RXF5EID0	0x1B
#define MCP_TEC			0x1C
#define MCP_REC			0x1D
#define MCP_RXM0SIDH	0x20
#define MCP_RXM0SIDL	0x21
#define MCP_RXM0EID8	0x22
#define MCP_RXM0EID0	0x23
#define MCP_RXM1SIDH	0x24
#define MCP_RXM1SIDL	0x25
#define MCP_RXM1EID8	0x26
#define MCP_RXM1EID0	0x27
#define MCP_CNF3		0x28
#define MCP_CNF2		0x29
#define MCP_CNF1		0x2A
#define MCP_CANINTE		0x2B
#define MCP_CANINTF		0x2C
#define MCP_EFLG		0x2D
#define MCP_TXB0CTRL	0x30
#define MCP_TXB1CTRL	0x40
#define MCP_TXB2CTRL	0x50
#define MCP_RXB0CTRL	0x60
#define MCP_RXB0SIDH	0x61
#define MCP_RXB1CTRL	0x70
#define MCP_RXB1SIDH	0x71


#define MCP_TX_INT		0x1C		// Enable all transmit interrupts
#define MCP_TX01_INT	0x0C		// Enable TXB0 and TXB1 interrupts
#define MCP_RX_INT		0x03		// Enable receive interrupts
#define MCP_NO_INT		0x00		// Disable all interrupts

#define MCP_TX01_MASK	0x14
#define MCP_TX_MASK		0x54

// Define SPI Instruction Set

#define MCP_WRITE		0x02

#define MCP_READ		0x03

#define MCP_BITMOD		0x05

#define MCP_LOAD_TX0	0x40
#define MCP_LOAD_TX1	0x42
#define MCP_LOAD_TX2	0x44

#define MCP_RTS_TX0		0x81
#define MCP_RTS_TX1		0x82
#define MCP_RTS_TX2		0x84
#define MCP_RTS_ALL		0x87

#define MCP_READ_RX0	0x90
#define MCP_READ_RX1	0x94

#define MCP_READ_STATUS	0xA0

#define MCP_RX_STATUS	0xB0

#define MCP_RESET		0xC0


// CANCTRL Register Values

#define MODE_NORMAL     0x00
#define MODE_SLEEP      0x20
#define MODE_LOOPBACK   0x40
#define MODE_LISTENONLY 0x60
#define MODE_CONFIG     0x80
#define MODE_POWERUP	0xE0
#define MODE_MASK		0xE0
#define ABORT_TX        0x10
#define MODE_ONESHOT	0x08
#define CLKOUT_ENABLE	0x04
#define CLKOUT_DISABLE	0x00
#define CLKOUT_PS1		0x00
#define CLKOUT_PS2		0x01
#define CLKOUT_PS4		0x02
#define CLKOUT_PS8		0x03


// CNF1 Register Values

#define SJW1            0x00
#define SJW2            0x40
#define SJW3            0x80
#define SJW4            0xC0


// CNF2 Register Values

#define BTLMODE			0x80
#define SAMPLE_1X       0x00
#define SAMPLE_3X       0x40


// CNF3 Register Values

#define SOF_ENABLE		0x80
#define SOF_DISABLE		0x00
#define WAKFIL_ENABLE	0x40
#define WAKFIL_DISABLE	0x00


// CANINTF Register Bits

#define MCP_RX0IF		0x01
#define MCP_RX1IF		0x02
#define MCP_TX0IF		0x04
#define MCP_TX1IF		0x08
#define MCP_TX2IF		0x10
#define MCP_ERRIF		0x20
#define MCP_WAKIF		0x40
#define MCP_MERRF		0x80


char can_read(int address){
	PORTB &= ~(1<<PB4);
	char instruction = 0b00000011;
	SPI_MasterTransmit(MCP_READ);
	SPI_MasterTransmit(address);
	char data = SPI_MasterRecieve();
	PORTB |= (1<<PB4);	
	return data;
}

void can_reset(){
	char reset_command = 0b11000000; // From table 12-1
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_RESET);
	PORTB |= (1<<PB4);	

}

void can_write(char address, char data){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_WRITE);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	PORTB |= (1<<PB4);	
}

void can_request_to_send(int buffer){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(buffer);
	PORTB |= (1<<PB4);
}

char can_read_status(){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_READ_STATUS);
	char data1 = SPI_MasterRecieve();
	char data2 = SPI_MasterRecieve();
	
	PORTB |= (1<<PB4);
	return data1;
}

char can_read_rx_status(){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_RX_STATUS);
	char data1 = SPI_MasterRecieve();
	char data2 = SPI_MasterRecieve();
	
	PORTB |= (1<<PB4);
	return data1;
}


void can_bit_modify_instruction(int address, int mask_byte, int data_byte){
	PORTB &= ~(1<<PB4);
	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(mask_byte);
	SPI_MasterTransmit(data_byte);
	PORTB |= (1<<PB4);
}

void can_send_message(int message_id, int8_t data){
	// message id 0-8
	// Load id to buffer 0
	int MCP_TXB0SIDL = 0x32;
	can_write(MCP_TXB0SIDL, 0b00100000); // TODO gj�r at det ikke er hardcodet
	int MCP_TXB0SIDH = 0x31;
	can_write(MCP_TXB0SIDH, 0b00000000);
	// load length
	int MCP_TXB0DLC = 0x35;
	can_write(MCP_TXB0DLC, 0b00000001);
	// load data
	int MCP_TXB0DM = 0x36;
	can_write(MCP_TXB0DM, data);
	
	// Enable buffer
	can_write(MCP_TXB0CTRL, 0b00001000);
	// Request to send buffer
	can_request_to_send(MCP_RTS_TX0);
}

int can_recieve_message(){
	// Wait for CANINTF.RX0IF flag to be high
	char status = can_read(MCP_TXB1CTRL);
	char data = can_read(MCP_CANINTF);
	//printf("%b \n\r", data);
	while(!(data & 0b00000010)){
		//data = can_read(MCP_CANINTF);
		printf("data is facked  %n \n\r", data);
		
	}
	
	
	int id_high = can_read(MCP_RXB1SIDH);
	int MCP_RXB1SIDL = 0x72;
	int id_low = can_read(MCP_RXB1SIDL);
	int MCP_RXB1DLC = 0x75;
	int data_lenght_buffer = can_read(MCP_RXB1DLC);
	int MCP_RXB1D0 = 0x76;
	int data1 = can_read(MCP_RXB1D0); 
	
	return data1;
}

uint8_t can_init(){
	SPI_MasterInit();
	//set configuration mode
	can_reset();
	_delay_ms(1000);
	char value = can_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf (" MCP2515 is NOT in configuration mode after reset !\n");
		return 1;
	} else {
		printf(" MCP2515 is in config mode");
	}
	
	can_write(MCP_CANCTRL, MODE_LOOPBACK);
	int d = can_read(MCP_CANSTAT);
	printf(" CANMODE = %d \n", d);
	
	can_write(MCP_CNF1, 0b00000011);
	can_write(MCP_CNF2, 0b10110001);
	can_write(MCP_CNF3, 0b00000101);
	can_write(MCP_CANINTE, (MCP_RX_INT | MCP_TX_INT));
	
	return 0;
	

}









#endif /* MCP2515_H_ */