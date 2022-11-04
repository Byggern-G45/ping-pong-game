/* atmega162_spi.c -- See atmega162_spi.h for info */

#define ATMEGA162_SPI_IMPORT
#include "../include/atmega162_spi.h"

char spi_tranceive(char data) {
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

void SPI_init(){
	/* Set MOSI and SCK output and SS, all others input */
	DDRB |= (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
	PORTB |= (1<<PB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
}


void SPI_Transmit(char data){
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
}


char SPI_Receive(void){
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}