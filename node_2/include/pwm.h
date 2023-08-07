/**
 * Library for using servo.
 */

#ifndef PWM_H
#define PWM_H

#ifdef PWM_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

#include <stdint.h>

/**
 * @brief Initialize PWM for servo
 */
void pwm_init();

/**
 * @brief Set the servo position
 * @param input position of servo
 */
void convert_to_pwm(uint8_t input);

#undef PWM_IMPORT
#undef EXTERN
#endif
