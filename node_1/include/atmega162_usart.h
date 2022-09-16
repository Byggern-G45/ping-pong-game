/**
 * Library for using USART on ATmega162. Has functions for initialization, transmit and receive.
 */

#ifndef ATMEGA162_USART_H
#define ATMEGA162_USART_H

#include <avr/io.h>

#ifdef ATMEGA162_USART_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

// #define ATMEGA162_USART_FOSC 4915200 // External oscillator
// #ifndef ATMEGA162_USART_BAUD
//     #define ATMEGA162_USART_BAUD 9600
// #endif
// #define ATMEGA162_USART_PRESCALER 16
#define UBRR 31 // (ATMEGA162_USART_FOSC/(ATMEGA162_USART_BAUD*ATMEGA162_USART_PRESCALER) - 1)

/**
 * @brief Initilizes USART for transmit and receive with 8 data bits and 2 stop bits
 */
EXTERN void atmega162_usart_init();

/**
 * @brief Transmits one 8-bit ASCII character over USART
 * 
 * @param character ASCII character
 */
EXTERN void atmega162_usart_transmit(unsigned char character);

/**
 * @brief Checks incomming USART buffer for ASCII character. Returns NULL if none
 * 
 * @return unsigned char, ASCII character
 */
EXTERN unsigned char atmega162_usart_receive();

#undef ATMEGA162_USART_IMPORT
#undef EXTERN
#endif