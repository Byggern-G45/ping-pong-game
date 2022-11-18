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

/**
 * @brief Initialize solenoid
 */
void solenoid_init();

/**
 * @brief Set the solenoid
 * @param input 0 is out, 1 is in
 */
void solenoid(uint8_t input);


#undef PWM_IMPORT
#undef EXTERN
#endif