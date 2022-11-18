/*
 * regulator.c
 */

#include "../include/regulator.h"
#include "../include/motor.h"
#include "../include/printf-stdarg.h"
#include "../include/timer.h"

struct pi_inputs_t {
    uint8_t* joystick_ptr;
    //int8_t* encoder_ptr;
} pi_inputs;

void pi_regulator_init(uint8_t* joystick_ptr/*, int8_t* encoder_ptr*/) {
    pi_inputs.joystick_ptr = joystick_ptr;
    //pi_inputs.encoder_ptr = encoder_ptr;
}

void regulate() {
    //if (TC0->TC_CHANNEL[1].TC_SR & TC_SR_CPCS) {
        static int integral_term = 0;

        uint8_t joystick = *pi_inputs.joystick_ptr;
        int8_t mapped_joystick = (int)joystick*200/255 - 100; // Map joystick value to -100 to 100
        int8_t encoder = motor_read_position();
        
        //printf("Joystick: %d, Encoder: %d\n", mapped_joystick, encoder);
        int error = (mapped_joystick - encoder);
        int proportional_term = Kp*error;
        integral_term += Ki*integral_term*error/1000; // Divide by 1000 to convert from ms to s
        int speed = proportional_term + integral_term;

        if (speed > 100) { // Ensure that speed is within bounds
            speed = 100;
        } else if (speed < -100) {
            speed = -100;
        }

        motor_set_speed(speed);
}
