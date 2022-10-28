/**
 * Library for using external CAN on ATmega162. Has function for initialization.
 */

#ifndef ATMEGA162_CAN_H
#define ATMEGA162_CAN_H

#include <avr/io.h>

#ifdef ATMEGA162_CAN_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


#undef ATMEGA162_CAN_IMPORT
#undef EXTERN
#endif