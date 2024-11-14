/*
 * tests.h
 *
 * Created: 02.10.2024 11:08:15
 *  Author: eveneha
 */ 
#pragma once
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "oled.h"
#include "external_memory_bus.h"
#include "mcp2515.h"


#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>
#include <stdbool.h>


#ifndef TESTS_H_
#define TESTS_H_

void test_lab_3(){
	init_external_memory_bus();
	init_UART();
	flush_UART();
	printf("line");
	SRAM_test();
	printf("nytt prog");
	init_clock_adc();
	while(1){
		adc_channels readings = read_channels();
		printf("value ch1");
		printf("The value of myNumber is: %d %d %d %d\n\r ", readings.joystick_left_right, readings.joystick_up_down, readings.shoot_button, readings.slider_right);
		_delay_ms(10);
	}
}

void test_lab_4(){
	init_external_memory_bus();
	oled_init();
	oled_clear_screen();
	while(1){
		oled_print_string("pikk", 1,0);
		_delay_ms(1000);
		oled_clear_screen();
		oled_print_string("pung", 0,0);
		_delay_ms(1000);
		oled_clear_screen();
		_delay_ms(1000);
	}
}

void test_oled() {
	init_external_memory_bus();
	oled_init();
	oled_show_main_menu();
	oled_clear_line(2); 
	oled_print_string("> New Game", 2,1);
	oled_clear_line(3); 
	oled_clear_line(4); 
	oled_clear_line(5); 
}

/*
typedef struct {
	uint8_t durations[4]; // Array to hold the duration values
	uint8_t selected_index; // Index of the currently selected duration
} GameDurationSettings;

GameDurationSettings game_duration_settings = {
	.durations = {15, 30, 45, 60}, // Initialize with durations of 15, 30, 45, and 60 seconds
	.selected_index = 1 // Default to the first duration (15 seconds)
};

#define NUM_USERS 5

typedef struct {
	const char *user_names[NUM_USERS]; // Array to hold user names
	uint16_t scores[NUM_USERS];        // Array to hold each user's score
	uint8_t selected_user_index;       // Index of the currently selected user
} Scoreboard;

Scoreboard scoreboard = {
	.user_names = {"Jo Arve", "Studass", "Kristoffer", "Alf", "Even"}, // Initialize with user names
	.scores = {0, 0, 0, 0, 0},         // Initialize all scores to 0
	.selected_user_index = 0           // Default to the first user, "Jo Arve"
};

int current_score;

void sort_scoreboard(Scoreboard *scoreboard) {
	uint8_t i, j;
	for (i = 0; i < NUM_USERS - 1; i++) {
		for (j = 0; j < NUM_USERS - i - 1; j++) {
			if (scoreboard->scores[j] > scoreboard->scores[j + 1]) {
				// Swap scores
				uint16_t temp_score = scoreboard->scores[j];
				scoreboard->scores[j] = scoreboard->scores[j + 1];
				scoreboard->scores[j + 1] = temp_score;

				// Swap corresponding user names
				char *temp_name = scoreboard->user_names[j];
				scoreboard->user_names[j] = scoreboard->user_names[j + 1];
				scoreboard->user_names[j + 1] = temp_name;
			}
		}
	}
}
void update_scoreboard(Scoreboard *scoreboard, uint8_t user_index, uint16_t new_score) {
	if (user_index < NUM_USERS) {
		if (new_score < scoreboard->scores[user_index] ) {
			scoreboard->scores[user_index] = new_score;
		}
	}
}
 

typedef enum {
    STATE_NEW_GAME,
    STATE_INSTRUCTIONS,
    STATE_SCOREBOARD,
    STATE_SET_DURATION
} MainMenuPtrState;

typedef enum {
	FIFTEEEN, 
	THIRTY, 
	FORTYFIVE,
	SIXTY 
} SetDurationPtrState;


typedef enum {
	MAIN_MENU, 
	NEW_GAME,
	PLAYING_GAME,
	INSTRUCTIONS, 
	SCOREBOARD, 
	SET_DURATION	
} GUIScreen;

int main_menu_marked_inst = 0; 
int main_menu_marked_inst2 = 0;

void fsm_main() {
	init_external_memory_bus();
	init_UART();
	flush_UART();
	stdout = &uart_out;
	
	GUIScreen screen = MAIN_MENU;  
	GUIScreen nextScreen;
	
	MainMenuPtrState mainMenuPtr = STATE_NEW_GAME;  
	MainMenuPtrState nextmainMenuPtr; 
	
	SetDurationPtrState currentDur = THIRTY; 
	SetDurationPtrState nextDur; 
	
	init_external_memory_bus();
	oled_init();
	oled_show_main_menu(); 
	
	
	init_clock_adc();
	
	adc_channels readings;
	
	
	//if(readings.joystick_up_down == 255 || readings.joystick_up_down == 0 || readings.shoot_button ==  255) {
	while(1){
		readings = read_channels();
		
		switch(screen) {
			case MAIN_MENU: 
				switch(mainMenuPtr) {
					case STATE_NEW_GAME:
						//oled_clear_screen();
						oled_show_main_menu();
						oled_clear_line(2); 
						oled_print_string("> New Game", 2,0); 
				
						if (readings.joystick_up_down > 230) {
							nextmainMenuPtr = STATE_SET_DURATION; 
						} else if (readings.joystick_up_down < 50) {
							nextmainMenuPtr = STATE_INSTRUCTIONS; 
						} 
						
						if (readings.shoot_button == 255) {
							nextScreen = NEW_GAME; 
						}			  
				
						break;
					case STATE_INSTRUCTIONS:
						oled_show_main_menu();
						oled_clear_line(3); 
						oled_print_string("> Instructions", 3,0); 	
				
						if (readings.joystick_up_down > 230) {
							nextmainMenuPtr = STATE_NEW_GAME;
							} else if (readings.joystick_up_down < 50) {
							nextmainMenuPtr = STATE_SCOREBOARD;
						}
						
						if (readings.shoot_button == 255) {
							nextScreen = INSTRUCTIONS;
						}
							
						break; 
					case STATE_SCOREBOARD: 
						oled_show_main_menu();
						oled_clear_line(4); 
						oled_print_string("> Scoreboard", 4,0); 
				
						if (readings.joystick_up_down > 230) {
							nextmainMenuPtr = STATE_INSTRUCTIONS;
							} else if (readings.joystick_up_down < 50) {
							nextmainMenuPtr = STATE_SET_DURATION;
						}
						
						if (readings.shoot_button == 255) {
							nextScreen = SCOREBOARD;
						}
				
						break;
					case STATE_SET_DURATION: 
						oled_show_main_menu();
						oled_clear_line(5); 
						oled_print_string("> Set Durations", 5,0); 
				
						if (readings.joystick_up_down > 230) {
							nextmainMenuPtr = STATE_SCOREBOARD;
							} else if (readings.joystick_up_down < 50) {
							nextmainMenuPtr = STATE_NEW_GAME;
						}
						
						if (readings.shoot_button == 255) {
							nextScreen = SET_DURATION;
						}
				
						break;   	
				}
				if (mainMenuPtr != nextmainMenuPtr) {
					oled_clear_screen();
				}
				mainMenuPtr = nextmainMenuPtr;
				break; 
				
				
			case NEW_GAME:
				current_score = 0; 
				can_message *recieved_message;
				send_commands_to_node_2_can();
				can_recieve_message(recieved_message);
				nextScreen = PLAYING_GAME;
				
				break; 
				
			case PLAYING_GAME:
				can_message *recieved_message;
				send_commands_to_node_2_can();
				can_recieve_message(recieved_message);
				int detected_score = recieved_message->data[0];
				if (detected_score){
					current_score = current_score + 1;
				}
				break;
				
				
			case INSTRUCTIONS: 
				switch (main_menu_marked_inst) {
					case 0: 
						oled_show_inst();
						break; 
					case 1: 
						oled_show_inst();
						oled_clear_line(7);
						oled_print_string("> Main Menu", 7,81);
						break; 
				}
				if (readings.joystick_up_down < 50) {
					main_menu_marked_inst = 1; 
				}else if (readings.joystick_up_down > 230) {
					main_menu_marked_inst = 0; 
				}
				if (main_menu_marked_inst == 1 && readings.shoot_button == 255) {
					nextScreen = MAIN_MENU; 
				}
				
				break; 
			
			case SCOREBOARD:
				
				
				switch (main_menu_marked_inst2) {
					case 0:
						oled_show_scoreboard();
						// you already have a sorted scoreboard from calling sort and update scoreboard
						for (int i = 0; i < NUM_USERS; i++) {
							oled_print_string(scoreboard.user_names[i],i+1, 0);
							oled_print_string(scoreboard.scores[i],i+1, 113);
						}
						
						
					break;
					case 1:
						oled_show_scoreboard();
						// you already have a sorted scoreboard from calling sort and update scoreboard
						for (int i = 0; i < NUM_USERS; i++) {
							oled_print_string(scoreboard.user_names[i],i+1, 0);
							oled_print_string(scoreboard.scores[i],i+1, 113);
						}
						oled_clear_line(7);
						oled_print_string("> Main Menu", 7,78);
					break;
				}
				if (readings.joystick_up_down < 50) {
					main_menu_marked_inst2 = 1;
					}else if (readings.joystick_up_down > 230) {
					main_menu_marked_inst2 = 0;
				}
				if (main_menu_marked_inst2 == 1 && readings.shoot_button == 255) {
					nextScreen = MAIN_MENU;
				}
				
				
				
				break; 
				
			case SET_DURATION:			
				switch (currentDur)
				{
				case FIFTEEEN:
					oled_show_duration();
					oled_clear_line(2);
					oled_print_string("> 15 seconds", 2,0);
					
					if (readings.joystick_up_down > 230) {
						nextDur = SIXTY;
						} else if (readings.joystick_up_down < 50) {
						nextDur = THIRTY;
					}
					
					if (readings.shoot_button == 255) {
						game_duration_settings.selected_index = 0; 
					}
					break;
					
				case THIRTY:
					oled_show_duration();
					oled_clear_line(3);
					oled_print_string("> 30 seconds", 3,0);
					
					if (readings.joystick_up_down > 230) {
						nextDur = FIFTEEEN;
						} else if (readings.joystick_up_down < 50) {
						nextDur = FORTYFIVE;
					}
					
					if (readings.shoot_button == 255) {
						game_duration_settings.selected_index = 1;
						nextScreen = MAIN_MENU; 
					}
					break;
				case FORTYFIVE:
					oled_show_duration();
					oled_clear_line(4);
					oled_print_string("> 45 seconds", 4,0);
				
					if (readings.joystick_up_down > 230) {
						nextDur = THIRTY;
						} else if (readings.joystick_up_down < 50) {
						nextDur = SIXTY;
					}
				
					if (readings.shoot_button == 255) {
						game_duration_settings.selected_index = 2;
						nextScreen = MAIN_MENU; 
					}
					break;
				case SIXTY:
					oled_show_duration();
					oled_clear_line(5);
					oled_print_string("> 60 seconds", 5,0);
					
					if (readings.joystick_up_down > 230) {
						nextDur = FORTYFIVE;
						} else if (readings.joystick_up_down < 50) {
						nextDur = FIFTEEEN;
					}
					
					if (readings.shoot_button == 255) {
						game_duration_settings.selected_index = 3;
						nextScreen = MAIN_MENU; 
					}
					break;
				}
				currentDur = nextDur; 			 
				break; 
			
			
		}
		if (nextScreen != screen) {
			oled_clear_screen(); 
		}
		screen = nextScreen; 
	

		
		 
		printf("Current state:\t\t %d\n\r", mainMenuPtr);
		printf("Next state: \t\t %d\n\r", nextmainMenuPtr);

		printf("joystick up down: \t%i\n\r", readings.joystick_up_down); 
		
		//_delay_ms(100);  
		
	}
}
*/

void test_lab_5(){
	init_external_memory_bus();
	init_UART();
	flush_UART();
	stdout = &uart_out;
	printf("test");
	int fail = can_init(MODE_LOOPBACK);
	if (!fail){
		printf("successfully initializes");
	}
	uint8_t i = 0;
	while (1)
	{
		can_message msg_send;
		msg_send.id_lower = 0b00100000;
		msg_send.id_higher = 0b00000000;
		msg_send.message_length_bytes = 8;
		
		msg_send.data[0] = i;
		msg_send.data[1] = i+1;
		msg_send.data[2] = i+2;
		msg_send.data[3] = i+3;
		msg_send.data[4] = i+4;
		msg_send.data[5] = i+5;
		msg_send.data[6] = i+6;
		msg_send.data[7] = i+7;
		can_send_message(msg_send);
				
		can_message *recieved_msg;
		can_recieve_message(recieved_msg);
		
		bool messages_are_the_same = true;
		
		for (uint8_t ii = 0; ii < msg_send.message_length_bytes; ++ii ){
			if (!(msg_send.data[ii] == recieved_msg->data[ii])){
				messages_are_the_same = false;
				break;
			}
		}
		
		if (messages_are_the_same){
			printf("messages are the same:)");
		} else {
			printf("!!! messages are not the same:(((");
		}
		
		_delay_ms(1000);
		
		i = i + 8;
		
		if (i > 100){
			break;
		}
		
	}
}

void can_loopback_test() {
	// To be placed inside empty main function 
	init_external_memory_bus();
	init_UART();
	flush_UART();
	stdout = &uart_out;
	printf("test");
	int fail = can_init(MODE_NORMAL);
	if (!fail){
		printf("successfully initializes");
	}
	init_UART();

	while(1){
		can_message msg_send;
		msg_send.id_lower = 0b00100000;
		msg_send.id_higher = 0b00000000;
		msg_send.message_length_bytes = 8;
		uint8_t i = 0;
		msg_send.data[0] = i;
		msg_send.data[1] = i+1;
		msg_send.data[2] = i+2;
		msg_send.data[3] = i+3;
		msg_send.data[4] = i+4;
		msg_send.data[5] = i+5;
		msg_send.data[6] = i+6;
		msg_send.data[7] = i+7;
		can_send_message(msg_send);
		printf("sent: ");
		for (uint8_t ii = 0; ii < msg_send.message_length_bytes; ++ii ){
			printf(" %i", msg_send.data[ii]);
		}
		printf(" \n\r");
		_delay_ms(1000);
	}
	
}

void adc_test(){
	init_external_memory_bus();
	volatile char *ext_adc = (char *) 0x1400;
	uint16_t ext_adc_size = 0x400;
	printf("testing ADC");
	oled_clear_screen();
	for (uint16_t i = 0; i < ext_adc_size; i++) {
		_delay_ms(100);
		uint8_t some_value = rand();
		ext_adc[i] = some_value;
	}
	printf("finished testing");
}




#endif /* TESTS_H_ */