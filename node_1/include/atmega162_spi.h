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

char spi_tranceive(char data);

void SPI_init();

void SPI_Transmit(char data);

char SPI_Receive(void);


#undef ATMEGA162_SPI_IMPORT
#undef EXTERN
#endif