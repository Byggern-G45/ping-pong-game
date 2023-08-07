/**
 * Library for using servo.
 */

#ifndef IR_H
#define IR_H
#include "sam.h"

/**
 * @brief Initialize ADC for IR sensor.
 */
void ADC_init();

/**
 * @brief Get the value of the IR sensor. High value means no ball
 * @return value of IR sensor
 */
uint16_t get_IR_value();

/**
 * @brief Get how many times the ball has missed and light up the LED accordingly
 * @param reset resets the misses
 * @return amount of misses 
 */
uint8_t get_ball_misses(uint8_t reset);

#endif