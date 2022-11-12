/*
 * regulator.c
 */

#include "../include/regulator.h"
#include "../include/motor.h"
#include "../include/printf-stdarg.h"
#include "../include/timer.h"

struct pi_inputs_t {
    int8_t* joystick_ptr;
    //int8_t* encoder_ptr;
} pi_inputs;

void pi_regulator_init(int8_t* joystick_ptr/*, int8_t* encoder_ptr*/) {
    timer_init();
    pi_inputs.joystick_ptr = joystick_ptr;
    //pi_inputs.encoder_ptr = encoder_ptr;
}

void TC0_handler() {
    // if (TC0->TC_CHANNEL[1].TC_SR & TC_SR_CPCS) {
    //     static int integral_term = 0;

    //     int error = (*pi_inputs.joystick_ptr - motor_read_position());
    //     int proportional_term = Kp*error;
    //     integral_term += Ki*integral_term*error*PERIOD/1000; // Divide by 1000 to convert from ms to s

    //     printf("Joystick: %d\t", *pi_inputs.joystick_ptr);
    //     printf("Error: %d\t", error);
    //     printf("P term: %d\t", proportional_term);
    //     printf("I term: %d\t", integral_term);
    //     printf("Speed: %d\n", proportional_term + integral_term);

    //     //motor_set_speed(proportional_term + integral_term);
    // }
}
