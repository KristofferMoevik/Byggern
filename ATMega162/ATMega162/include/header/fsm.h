/*
 * fsm.h
 *
 * Created: 14.11.2024 09:53:27
 *  Author: eveneha
 */ 


#ifndef FSM_H_
#define FSM_H_

#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "oled.h"
#include "tests.h"
#include "mcp2515.h"
#include "joystick.h"
#include "node_communication.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <time.h>

// Global variables
int current_tick;
int ticks_per_second = 10;
int current_score;
can_message *recieved_message;

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
				current_tick = 0;
				printf("Newgame"); 
				send_commands_to_node_2_can();
				can_recieve_message(recieved_message);
				nextScreen = PLAYING_GAME;
				
				break; 
				
			case PLAYING_GAME:
				
				send_commands_to_node_2_can();
				can_recieve_message(recieved_message);
				int detected_score = recieved_message->data[0];
				if (detected_score){
					current_score = current_score + 1;
				}
				
				current_tick = current_tick + 1;
				int play_for = game_duration_settings.durations[game_duration_settings.selected_index];
				printf("play for: %i, played: %i", (ticks_per_second*play_for), current_tick);
				if (current_tick > (ticks_per_second*play_for)){
					nextScreen = SCOREBOARD;
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



#endif /* FSM_H_ */