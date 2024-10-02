/*
 * oled.c
 *
 * Created: 25.09.2024 11:04:32
 *  Author: eveneha
 */ 

#pragma once
#include "oled.h"
#include <avr/pgmspace.h>

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
    send_command(0x02);  // set to page addressing mode
	
    send_command(0xDB);  // VCOM deselect level mode
    send_command(0x30);  // deselect level value
	
    send_command(0xAD);  // master configuration
    send_command(0x00);  // master config value
	
    send_command(0xA4);  // output follows RAM content
    send_command(0xA6);  // set normal display
    send_command(0xAF);  // display on
	
}


void oled_clear_screen(){
	oled_goto_pos(0,0);
	int pages = 8;
	int coloums = 128;
	for (int i = 0; i < pages; i++){
		oled_goto_pos(i,0);
		for (int ii = 0; i > coloums; i++){
			send_data(0x00);	
		}
	}
}

void oled_goto_pos(int page_start, int segment){
	send_command(0xB0 | page_start); // Set page
	send_command(segment & 0x0F);
	send_command(((segment & 0xf0) >> 4) | (0x10));
}

void send_char(char c){
	for (int i = 0; i < font_size; i++){
		char letter_byte = pgm_read_byte(&font5[c][i]);
		send_data(letter_byte);
	}
	
}

void oled_write_char_to_pos(char c, int page, int col){
	oled_goto_pos(page,col);
	send_char(c);
}

void oled_print_string(char str[]){
	for (int i = 0; i < strlen(str); i++){
		send_char(str[i]);
	}
}


