/**
 * Library for using external SPI on ATmega162. Has function for initialization.
 */

#ifndef ATMEGA162_SPI_H
#define ATMEGA162_SPI_H

#include <avr/io.h>

#ifdef ATMEGA162_SPI_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


#undef ATMEGA162_SPI_IMPORT
#undef EXTERN
#endif