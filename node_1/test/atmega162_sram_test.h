/**
 * Function for testing SRAM on ATmega162.
 */

#ifndef ATMEGA162_SRAM_TEST_H
#define ATMEGA162_SRAM_TEST_H

#include <avr/io.h>

#ifdef ATMEGA162_SRAM_TEST_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/**
 * @brief Initilizes external SRAM
 */
EXTERN void sram_test();

#undef ATMEGA162_SRAM_TEST_IMPORT
#undef EXTERN
#endif