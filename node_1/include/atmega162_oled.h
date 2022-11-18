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

/**
 * @brief Write command to OLED
 * @param command 
 */
void write_c(uint8_t command);

/**
 * @brief Write data to OLED
 * @param command 
 */
void write_d(uint8_t command);

/**
 * @brief Initialize OLED
 */
void oled_init();

/**
 * @brief Clear OLED
 */
void oled_reset();

/**
 * @brief Sets cursor to (0,0)
 */
void oled_home();

/**
 * @brief Sets cursor to first in row
 * @param line row
 */
void oled_goto_line(uint8_t line);

/**
 * @brief Sets cursor to column
 * @param column
 */
void oled_goto_column(uint8_t column);

/**
 * @brief Clears a row
 * @param line row
 */
void oled_clear_line(uint8_t line);

/**
 * @brief Sets cursor to (line,column)
 * @param line row
 * @param column
 */
void oled_pos(uint8_t line, uint8_t column);

/**
 * @brief Write a string to OLED
 * @param data, string
 */
void oled_print(char* data);

#undef ATMEGA162_OLED_IMPORT
#undef EXTERN
#endif