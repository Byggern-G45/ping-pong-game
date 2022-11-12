/*
 * regulator.h
 */ 

#ifndef REGULATOR_H_
#define REGULATOR_H_

#include <sam.h>

#define Kp      1
#define Ki      1
#define PERIOD 17 // 60Hz, 16,666ms period

void pi_regulator_init();
void TC0_handler();

#endif /* REGULATOR_H_ */