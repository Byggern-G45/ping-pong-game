/*
 * motor.h
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

void motor_init();
void motor_set_speed(int speed);
int motor_read_position();

#endif /* CAN_INTERRUPT_H_ */