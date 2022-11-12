/**
 * Library for using solenoid.
 */

#ifndef SOLENOID_H
#define SOLENOID_H


#ifdef SOLENOID_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

#include <stdint.h>

void solenoid_init();

void solenoid(uint8_t input);


#undef PWM_IMPORT
#undef EXTERN
#endif