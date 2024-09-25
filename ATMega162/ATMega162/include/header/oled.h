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


const uint8_t font5x7[26][5];

void oled_init();
void oled_clear_display();
void oled_write_char(char c);
void oled_printf(char text[]);





#endif /* OLED_H_ */
