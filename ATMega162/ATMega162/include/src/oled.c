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
		for (int ii = 0; ii < coloums; ii++){
			send_data(0x0);	
		}
	}
}

void oled_clear_line(int line){
	oled_goto_pos(line,0);
	int coloums = 128;	
	for (int ii = 0; ii < coloums; ii++){
		send_data(0x0);	
	}
	
}

void oled_goto_pos(int page_start, int segment){
	send_command(page_start	| 0xB0); // Set page
	send_command(segment & 0x0F);
	send_command(((segment & 0xF0) >> 4) | (0x10));
}

void send_char(char c){
	for (int i = 0; i < font_size; i++){
		char letter_byte = pgm_read_byte(&font5[c - 32][i]);
		send_data(letter_byte);
	}
	
}

void oled_print_string(char str[], int line, int pos){
	oled_goto_pos(line, pos);
	for (int i = 0; i < strlen(str); i++){
		send_char(str[i]);
	}
}

void oled_show_main_menu() {
	//oled_clear_screen();
	const char *menu_items[] = {"New Game", "Instructions", "Scoreboard", "Set Duration"};
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);

	//oled_goto_pos(1,20);
	oled_print_string("Main Menu", 1, 35);

    for (int i = 2; i < num_items+2; i++) {
        oled_goto_pos(i, 0); // One item per page
		//oled_print_string(" ",i); 
		oled_print_string(menu_items[i-2],i,0);
    }
}

void oled_show_inst() {
	//oled_clear_screen();

	oled_goto_pos(0,20);
	oled_print_string("INSTRUCTIONS",1,30);

	//oled_goto_pos(1,0);
	oled_print_string("Controll the shooter with", 2,0);
	//oled_goto_pos(2,0);
	oled_print_string("slider and joystick.",3,0);
	//oled_goto_pos(3,0);
	oled_print_string("Shoot by pressing button.",4,0);
	//oled_goto_pos(4,0);
	oled_print_string("Score as many goals as", 5,0); 
	oled_print_string("possible within the limit",6,0);

	oled_print_string("Main Menu",7,83);
}

void oled_show_duration() {
	//oled_clear_screen(); 
	oled_print_string("Set Game Duration", 1, 30); 
	oled_print_string("15 seconds", 2,0); 
	oled_print_string("30 seconds", 3,0);
	oled_print_string("45 seconds", 4,0);
	oled_print_string("60 seconds", 5,0);
}

void oled_show_scoreboard() {
	//oled_clear_screen(); 
	oled_print_string("Scoreboard", 0 ,30); 
	oled_print_string("Main menu", 7, 83 ); 
	 
}



