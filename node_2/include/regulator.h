/*
 * regulator.h
 */ 

#ifndef REGULATOR_H_
#define REGULATOR_H_

#include <sam.h>

#define Kp      1.2
#define Ki      50
#define PERIOD  1 // Currently uses main loop period

/**
 * @brief Initialize PI regulator
 * @param joystick_ptr pointer to joystick value
 */
void pi_regulator_init(uint8_t* joystick_ptr/*, int8_t* encoder_ptr*/);

/**
 * @brief Regulate the motor speed based on encoder and joystick
 */
void regulate();

#endif /* REGULATOR_H_ */