/**
 * Library for using external SRAM on ATmega162. Has function for initialization.
 */

#ifndef ATMEGA162_SRAM_H
#define ATMEGA162_SRAM_H

#include <avr/io.h>

#ifdef ATMEGA162_SRAM_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/**
 * @brief Initilizes external SRAM
 */
EXTERN void sram_init();

EXTERN uint8_t sram_test();


#undef ATMEGA162_SRAM_IMPORT
#undef EXTERN
#endif