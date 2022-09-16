/**
 * Library for using external SRAM on ATmega162. Has function for initialization.
 */

#ifndef ATMEGA162_JOYSTICK_H
#define ATMEGA162_JOYSTICK_H

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef ATMEGA162_JOYSTICK_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/**
 * @brief Initilizes external SRAM
 */
EXTERN void atmega162_joystick_init();

/**
 * @brief 
 */
EXTERN void atmega162_joystick_start_conversion();

/**
 * @brief 
 */
EXTERN uint8_t atmega162_joystick_read();

#undef ATMEGA162_JOYSTICK_IMPORT
#undef EXTERN
#endif