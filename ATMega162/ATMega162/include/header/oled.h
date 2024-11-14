/*
 * oled.h
 *
 * Created: 25.09.2024 11:04:57
 *  Author: eveneha
 */

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "fonts.h"

#include "addresses.h"

#ifndef OLED_H_
#define OLED_H_

#define OLED_WIDTH 128
#define OLED_HEIGHT	64 
#define OLED_PAGES 8 

#define OLED_CONTROL *((volatile char*)ADDR_BASE + ADDR_OFFSET_OLED_C)
#define OLED_DATA *((volatile char*)ADDR_BASE + ADDR_OFFSET_OLED_D)


void oled_init();
void oled_clear_screen();
void oled_clear_line(int line);
void oled_goto_pos(int line, int col);
void send_char(char c);
void oled_write_char_to_pos(char c, int page, int col);
void oled_print_string(char str[], int line, int pos);
void oled_show_main_menu(); 
void oled_show_inst(); 
void oled_show_duration(); 
void oled_show_scoreboard(); 

#endif /* OLED_H_ */
