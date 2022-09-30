/**
 * Library for using MAX155 ADC for joystick measurements. Has function for initialization,
 * starting conversion, and a struct that holds the values.
 */

#ifndef ATMEGA162_ADC_H
#define ATMEGA162_ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef ATMEGA162_ADC_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

typedef enum direction_t {
    LEFT, 
    RIGHT, 
    UP, 
    DOWN, 
    NEUTRAL
};

typedef struct joystick_t {
	volatile uint8_t position[2];
	volatile uint8_t correction[2];
    volatile direction_t direction;
};

typedef struct slider_t {
    volatile uint8_t position;
};

joystick_t joystick;
slider_t left_slider;
slider_t right_slider;

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
EXTERN void joystick_calibrate();

/**
 * @brief Maps a value between 0-255 to 0-100
 * 
 * @param byte Value to be mapped
 * @return uint8_t Mapped value
 */
EXTERN int8_t to_percentage(uint8_t byte);

#undef ATMEGA162_ADC_IMPORT
#undef EXTERN
#endif