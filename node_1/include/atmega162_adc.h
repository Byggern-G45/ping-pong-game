/**
 * Library for using MAX155 ADC for joystick measurements. Has function for initialization,
 * starting conversion, and a struct that holds the values.
 */

#ifndef ATMEGA162_ADC_H
#define ATMEGA162_ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#ifdef ATMEGA162_ADC_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

typedef enum {
    LEFT, 
    RIGHT, 
    UP, 
    DOWN, 
    NEUTRAL
} direction_t;

typedef struct {
	volatile uint8_t position[2];
	volatile int8_t correction[2];
    volatile direction_t direction;
} joystick_t;

typedef struct {
    volatile uint8_t position;
} slider_t;

/**
 * @brief Initilizes Clk for ADC and enables interrupts
 */
EXTERN void adc_init();

/**
 * @brief Starts ADC conversion if another conversion is not currently happening
 */
EXTERN void adc_start_conversion();

/**
 * @brief Reads the ADC channels and stores the values in the joystick struct
 */
void _adc_read();

/**
 * @brief Reads state of the joystick button on PB0
 */
EXTERN uint8_t joystick_button_read();

/**
 * @brief Calibrates the joystick by reading the current position and storing it as the
 *        correction value.
 */
void _joystick_calibrate();

/**
 * @brief Calculates the direction of the joystick based on the percentage position
 * 
 * @param position The position of the joystick in percentage
 */
void _calculate_direction();

/**
 * @brief Maps a value between 0-255 to 0-100
 * 
 * @param byte Value to be mapped
 * @return uint8_t Mapped value
 */
EXTERN int8_t to_percentage(uint8_t byte);

EXTERN uint8_t get_joystick_x();

EXTERN uint8_t get_joystick_y();

EXTERN uint8_t get_slider_left();

EXTERN uint8_t get_slider_right();

#undef ATMEGA162_ADC_IMPORT
#undef EXTERN
#endif