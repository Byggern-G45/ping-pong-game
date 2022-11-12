/**
 * Library for using servo.
 */

#ifndef IR_H
#define IR_H
#include "sam.h"


void ADC_init();

uint16_t get_IR_value();

#endif