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

void pi_regulator_init(int8_t* joystick_ptr/*, int8_t* encoder_ptr*/) {
    timer_init();
    pi_inputs.joystick_ptr = joystick_ptr;
    //pi_inputs.encoder_ptr = encoder_ptr;
}

void TC0_Handler() {
    //if (TC0->TC_CHANNEL[1].TC_SR & TC_SR_CPCS) {
        static int integral_term = 0;

        uint8_t joystick = *pi_inputs.joystick_ptr*200/255 - 100; // Map joystick value to -100 to 100
        int8_t encoder = motor_read_position();
        //printf("encoder: %d\n", encoder);
        int error = (joystick - motor_read_position());
        //printf("error: %d\n", error);
        int proportional_term = Kp*error;
        //integral_term += Ki*integral_term*error*PERIOD/1000; // Divide by 1000 to convert from ms to s

        // printf("Joystick: %d\t", *pi_inputs.joystick_ptr);
        // printf("Error: %d\t", error);
        // printf("P term: %d\t", proportional_term);
        // printf("I term: %d\t", integral_term);
        // printf("Speed: %d\n", proportional_term + integral_term);

        // for (int i = 0; i < 1000; i++) {
        //     asm("nop");
        // }

        motor_set_speed(proportional_term + integral_term);
    //}
}
