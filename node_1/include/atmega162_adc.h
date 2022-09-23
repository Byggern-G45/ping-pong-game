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

/**
 * @brief Initilizes Clk for ADC and enables interrupts.
 */
EXTERN void atmega162_adc_init();

/**
 * @brief Starts ADC conversion if another conversion is not currently happening
 */
EXTERN void atmega162_adc_start_conversion();

/**
 * @brief Reads the ADC channels and stores the values in the joystick struct
 */
void atmega162_adc_read();

/**
 * @brief Reads state of the joystick button on PB0
 */
EXTERN uint8_t atmega162_joystick_button_read();

/**
 * @brief Calibrates the joystick by reading the current position and storing it as the
 * correction value.
 */
EXTERN void atmega162_joystick_calibrate();

/**
 * @brief Maps a value between 0-255 to 0-100
 * 
 * @param byte Value to be mapped
 * @return uint8_t Mapped value
 */
EXTERN uint8_t to_percentage(uint8_t byte);

#undef ATMEGA162_ADC_IMPORT
#undef EXTERN
#endif