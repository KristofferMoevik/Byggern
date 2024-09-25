/*
 * oled.c
 *
 * Created: 25.09.2024 11:04:32
 *  Author: eveneha
 */ 


#include "oled.h"
#include <avr/pgmspace.h>

volatile char *ext_oled = (char *)(ADDR_BASE + ADDR_OFFSET_OLED_C);

uint8_t (*oled_buffer)[OLED_WIDTH] = (uint8_t (*)[OLED_WIDTH])(ADDR_BASE + ADDR_OFFSET_SRAM);


const uint8_t font5x7[26][5] = {
	// Character 'A'
	{0x7C, 0x12, 0x11, 0x12, 0x7C},  // A
	// Character 'B'
	{0x7F, 0x49, 0x49, 0x49, 0x36},  // B
	// Character 'C'
	{0x3E, 0x41, 0x41, 0x41, 0x22},  // C
	// Character 'D'
	{0x7F, 0x41, 0x41, 0x41, 0x3E},  // D
	// Character 'E'
	{0x7F, 0x49, 0x49, 0x49, 0x41},  // E
	// Character 'F'
	{0x7F, 0x09, 0x09, 0x09, 0x01},  // F
	// Character 'G'
	{0x3E, 0x41, 0x49, 0x49, 0x7A},  // G
	// Character 'H'
	{0x7F, 0x08, 0x08, 0x08, 0x7F},  // H
	// Character 'I'
	{0x00, 0x41, 0x7F, 0x41, 0x00},  // I
	// Character 'J'
	{0x20, 0x40, 0x41, 0x3F, 0x01},  // J
	// Character 'K'
	{0x7F, 0x08, 0x14, 0x22, 0x41},  // K
	// Character 'L'
	{0x7F, 0x40, 0x40, 0x40, 0x40},  // L
	// Character 'M'
	{0x7F, 0x02, 0x0C, 0x02, 0x7F},  // M
	// Character 'N'
	{0x7F, 0x04, 0x08, 0x10, 0x7F},  // N
	// Character 'O'
	{0x3E, 0x41, 0x41, 0x41, 0x3E},  // O
	// Character 'P'
	{0x7F, 0x09, 0x09, 0x09, 0x06},  // P
	// Character 'Q'
	{0x3E, 0x41, 0x51, 0x21, 0x5E},  // Q
	// Character 'R'
	{0x7F, 0x09, 0x19, 0x29, 0x46},  // R
	// Character 'S'
	{0x46, 0x49, 0x49, 0x49, 0x31},  // S
	// Character 'T'
	{0x01, 0x01, 0x7F, 0x01, 0x01},  // T
	// Character 'U'
	{0x3F, 0x40, 0x40, 0x40, 0x3F},  // U
	// Character 'V'
	{0x1F, 0x20, 0x40, 0x20, 0x1F},  // V
	// Character 'W'
	{0x7F, 0x20, 0x18, 0x20, 0x7F},  // W
	// Character 'X'
	{0x63, 0x14, 0x08, 0x14, 0x63},  // X
	// Character 'Y'
	{0x03, 0x04, 0x78, 0x04, 0x03},  // Y
	// Character 'Z'
	{0x61, 0x51, 0x49, 0x45, 0x43},  // Z
};



void send_command(uint8_t cmd){
	OLED_CONTROL = cmd; 
}

void send_data(uint8_t data){
	OLED_DATA = data; 
}


void oled_init() {
    
	send_command(0xAE);  // display off
    send_command(0xA1);  // segment remap
    send_command(0xDA);  // common pads hardware: alternative
    send_command(0x12);  // send alternative pad configuration
    send_command(0xC8);  // common output scan direction: com63~com0
    send_command(0xA8);  // multiplex ratio mode: 63
    send_command(0x3F);  // ratio value
    send_command(0xD5);  // display divide ratio/oscillator frequency mode
    send_command(0x80);  // frequency value
    send_command(0x81);  // contrast control
    send_command(0x50);  // contrast value
    send_command(0xD9);  // set pre-charge period
    send_command(0x21);  // pre-charge value
    send_command(0x20);  // Set Memory Addressing Mode
    send_command(0x02);  // memory addressing value
    send_command(0xDB);  // VCOM deselect level mode
    send_command(0x30);  // deselect level value
    send_command(0xAD);  // master configuration
    send_command(0x00);  // master config value
    send_command(0xA4);  // output follows RAM content
    send_command(0xA6);  // set normal display
    send_command(0xAF);  // display on
	
}

void oled_write_data(char data){
	volatile char *OLED_write = (char *) 0x1200;
	*OLED_write = data; // Removed [0] from OLED_write
}

void oled_print(char c){
	int font_size = 5;
	for(uint8_t i = 0; i < font_size; i++){
		oled_write_data(pgm_read_byte(&font5[c - 32][i]));
	}
}

void oled_clear_display() {
	for (uint8_t page = 0; page < OLED_PAGES; page++) {
		for (uint8_t x = 0; x < OLED_WIDTH; x++) {
			oled_buffer[page][x] = 0x00; // All bits cleared
		}
	}
}


// Function to write a single character (requires a font array)
void oled_write_char(char c) {
	if (c < 32 || c > 127) return; // Character range check
	for (uint8_t i = 0; i < 5; i++) {
		send_data(pgm_read_byte(&font5x7[c - 32][i]));  // Use pgm_read_byte to read from PROGMEM
	}
	send_data(0x00); // Add space between characters
}


void oled_printf(char text[]){
	
}



