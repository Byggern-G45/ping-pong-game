/* atmega162_spi.c -- See atmega162_spi.h for info */

#define ATMEGA162_SPI_IMPORT
#include "../include/atmega162_spi.h"

char spi_tranceive(char data='\0') {
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}