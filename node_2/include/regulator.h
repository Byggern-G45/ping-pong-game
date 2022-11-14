/*
 * regulator.h
 */ 

#ifndef REGULATOR_H_
#define REGULATOR_H_

#include <sam.h>

#define Kp      0.2
#define Ki      30
#define PERIOD  1 // 60Hz, 16,666ms period

void pi_regulator_init(uint8_t* joystick_ptr/*, int8_t* encoder_ptr*/);
void regulate();

#endif /* REGULATOR_H_ */