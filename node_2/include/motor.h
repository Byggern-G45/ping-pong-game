/*
 * motor.h
 */ 

#ifndef MOTOR_H_
#define MOTOR_H_

#include <sam.h>

#define IN_ENCODER_MIN   2586 // Value of encoder when all the way to the right
#define IN_ENCODER_MAX  65274 // Value of encoder when all the way to the left
#define OUT_ENCODER_MIN     0 // Mapped value when all the way to the right
#define OUT_ENCODER_MAX   255 // Mapped value when all the way to the left

#define IN_SPEED_MIN        0 // Minimum value of speed
#define IN_SPEED_MAX      100 // Maximum value of speed
#define OUT_SPEED_MIN       0 // Mapped value when minimum speed
#define OUT_SPEED_MAX   65535 // Mapped value when maximum speed

/**
 * @brief Initialize motor and encoder
 */
void motor_init();

/**
 * @brief Set speed and direction of motor. Negative values are right, positive values are left.
 *        Value is mapped to 0-65535 and sent to DACC.
 * @param speed value between -100 and 100
 */
void motor_set_speed(int16_t speed);

/**
 * @brief Read position of motor with the encoder
 * @return position between -100 and 100
 */
uint8_t motor_read_position();

#endif /* MOTOR_H_ */