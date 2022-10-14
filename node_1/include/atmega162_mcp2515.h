/**
 * Library for using external MCP2515 on ATmega162. Has function for initialization.
 */

#ifndef ATMEGA162_MCP2515_H
#define ATMEGA162_MCP2515_H

#include <avr/io.h>

#ifdef ATMEGA162_MCP2515_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


#undef ATMEGA162_MCP2515_IMPORT
#undef EXTERN
#endif