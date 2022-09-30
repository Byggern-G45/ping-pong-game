/**
 * Library for using a OLED display with ATmega162.
 */

#ifndef ATMEGA162_OLED_H
#define ATMEGA162_OLED_H

#include <avr/io.h>

#ifdef ATMEGA162_OLED_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

void write_c(uint8_t command);

void write_d(uint8_t command);

void oled_init();

void oled_reset();

void oled_home();

void oled_goto_line(uint8_t line);

void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_pos(uint8_t row_column);

void oled_print(char* character);

#undef ATMEGA162_OLED_IMPORT
#undef EXTERN
#endif