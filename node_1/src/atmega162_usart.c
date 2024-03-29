/* atmega162_usart.c -- See atmega162_usart.h for info */

#define ATMEGA162_USART_IMPORT
#include "../include/atmega162_usart.h"

void usart_init() {
    UBRR0H = (unsigned char)(UBRR>>8);               // Set BAUD rate
    UBRR0L = (unsigned char)UBRR;
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);                // Enable receiver and transmitter
    UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00); // Set frame format: 8 data bit, 2 stop bit
}

void usart_transmit(unsigned char character) {
	while (!(UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer
	UDR0 = character;               // Put character into outgoing buffer
}

unsigned char usart_receive() {
    if (UCSR0A & (1<<RXC0)) { // If character has been received
        return UDR0;          // Get and return character from buffer
    }
    return '\0';              // Notify no character received
}