/**
 * Library for using servo.
 */

#ifndef TIMER_H
#define TIMER_H


#ifdef TIMER_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

void timer_init(void);


#undef TIMER_IMPORT
#undef EXTERN
#endif