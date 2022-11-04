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

void pwm_init();

void convert_to_pwm(uint8_t input);


#undef PWM_IMPORT
#undef EXTERN
#endif