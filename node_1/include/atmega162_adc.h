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

typedef enum {
    LEFT, 
    RIGHT, 
    UP, 
    DOWN, 
    NEUTRAL
} direction_t;

/**
 * @brief Struct for holding joystick position, direction and calibration values.
 */
typedef struct {
	volatile uint8_t position[2];
	volatile uint8_t correction[2];
    volatile direction_t direction;
} joystick_t;

/**
 * @brief Struct for holding slider position.
 */
typedef struct {
    volatile uint8_t position;
} slider_t;

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
 * @brief Reads the ADC channels and stores the position value in the joystick struct.
 *        The values are corrected with a calibrated value. This is not needed if the 
 *        position is not used since direction is calculated with margins
 */
void _adc_read();

/**
 * @brief Calibrates the joystick by reading the current position and storing it as the
 *        correction value
 */
void _joystick_calibrate();

/**
 * @brief Calculates the direction of the joystick based on the percentage position with
 *       a margin of 50
 */
void _calculate_direction();

/**
 * @brief Maps a value between 0-255 to 0-100
 * @param byte Value to be mapped
 * @return uint8_t Mapped value
 */
int8_t _to_percentage(uint8_t byte);

/**
 * @brief Reads state of the joystick button on PB0
 */
EXTERN uint8_t joystick_button_read();

#undef ATMEGA162_ADC_IMPORT
#undef EXTERN
#endif