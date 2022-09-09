/**
 * @copyright
 * @license MIT
 * @author
 * @version
 * @file
 */

#ifndef atmega162_usart_H
#define atmega162_usart_H

#include <avr/io.h>

#ifdef atmega162_usart_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

#define ATMEGA162_USART_FOSC 4915200 // External oscillator
#ifndef ATMEGA162_USART_BAUD
    #define ATMEGA162_USART_BAUD 9600
#endif
#define ATMEGA162_USART_PRESCALER 16
#define UBRR 31

/**
 * @brief Initilizes the USART for transmit and receive with 8 data bits and 2 stop bits
 */
EXTERN void atmega162_usart_init();

/**
 * @brief 
 * 
 * @param character 
 */
EXTERN void atmega162_usart_transmit(unsigned char character);

/**
 * @brief 
 * 
 * @return unsigned char 
 */
EXTERN unsigned char atmega162_usart_receive();

/**
 * @brief Empties the receive buffer
 */
EXTERN void atmega162_usart_flush();

#undef atmega162_usart_IMPORT
#undef EXTERN
#endif