/*
 * oled.c
 *
 * Created: 25.09.2024 11:04:32
 *  Author: eveneha
 */ 

#pragma once
#include "oled.h"

#include <avr/pgmspace.h>

void send_cmd_to_oled(uint8_t cmd){
	OLED_CONTROL_ADDRESS = cmd; 
}

void send_data_to_oled(uint8_t data){
	OLED_DATA_ADDRESS = data; 
}


void oled_init() {
    
	send_cmd_to_oled(0xAE);
    send_cmd_to_oled(0xA1);
    send_cmd_to_oled(0xDA);
    send_cmd_to_oled(0x12);
    send_cmd_to_oled(0xC8);
    
	send_cmd_to_oled(0xA8);
    send_cmd_to_oled(0x3F);
    
	send_cmd_to_oled(0xD5);
    send_cmd_to_oled(0x80);
	
    send_cmd_to_oled(0x81);
    send_cmd_to_oled(0x50);
	
    send_cmd_to_oled(0xD9);
    send_cmd_to_oled(0x21);
	
    send_cmd_to_oled(0x20);
    send_cmd_to_oled(0x02);
	
    send_cmd_to_oled(0xDB);
    send_cmd_to_oled(0x30);
	
    send_cmd_to_oled(0xAD);
    send_cmd_to_oled(0x00);
	
    send_cmd_to_oled(0xA4);
    send_cmd_to_oled(0xA6);
    send_cmd_to_oled(0xAF);
	
}


void oled_clear_screen(){
	oled_goto_pos(0,0);
	int pages = 8;
	int coloums = 128;
	for (int i = 0; i < pages; i++){
		oled_goto_pos(i,0);
		for (int ii = 0; ii < coloums; ii++){
			send_data_to_oled(0x0);	
		}
	}
}

void oled_clear_line(int line){
	oled_goto_pos(line,0);
	int coloums = 128;	
	for (int ii = 0; ii < coloums; ii++){
		send_data_to_oled(0x0);	
	}
	
}

void oled_goto_pos(int page_start, int segment){
	send_cmd_to_oled(page_start	| 0xB0);
	send_cmd_to_oled(segment & 0x0F);
	send_cmd_to_oled(((segment & 0xF0) >> 4) | (0x10));
}

void send_char(char c){
	for (int i = 0; i < font_size; i++){
		char letter_byte = pgm_read_byte(&font5[c - 32][i]);
		send_data_to_oled(letter_byte);
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
       // oled_goto_pos(i, 0); // One item per page
		//oled_print_string(" ",i); 
		oled_print_string(menu_items[i-2],i,0);
    }
}

void oled_show_inst() {
	//oled_clear_screen();

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

void oled_show_new_game( ) {
	oled_print_string("Pick user", 0, 30); 	
}





