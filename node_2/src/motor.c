/*
 * motor.c
 */ 

#include "../include/motor.h"
#include <stdio.h>
#include <sam.h>

void motor_init() {
    /********************************************************************
     * Motorbox in MJ1
     * PD0       -> PIN25         -> !OE       -- encoder
     * PD1       -> PIN26         -> !RST      -- encoder
     * PD2       -> PIN27         -> SEL       -- encoder
     * PD9       -> PIN30         -> EN        -- motor
     * PD10      -> PIN32         -> DIR       -- motor
     ********************************************************************/

    // Enable PIOs
    PIOD->PIO_PER |= PIO_PER_P0 | // !OE
                     PIO_PER_P1 | // !RST
                     PIO_PER_P2 | // SEL
                     PIO_PER_P9 | // EN
                     PIO_PER_P10; // DIR
    // Set PIOs as output               
    PIOD->PIO_OER |= PIO_OER_P0 | // !OE
                     PIO_OER_P1 | // !RST
                     PIO_OER_P2 | // SEL
                     PIO_OER_P9 | // EN
                     PIO_OER_P10; // DIR
                     
    /********************************************************************
     * Motorbox out MJ2
     * PC1...PC8 -> PIN33...PIN40 -> DO0...DO7 -- counter
     ********************************************************************/

    // Enable PIOs
    PIOC->PIO_PER |= PIO_PER_P1 |
                     PIO_PER_P2 |
                     PIO_PER_P3 |
                     PIO_PER_P4 |
                     PIO_PER_P5 |
                     PIO_PER_P6 |
                     PIO_PER_P7 |
                     PIO_PER_P8;


    PIOD->PIO_SODR |= PIO_SODR_P9;  // Enable motor
	PIOD->PIO_CODR |= PIO_CODR_P10; // Set motor direction
	PIOD->PIO_SODR |= PIO_SODR_P1;  // Disable reser encoder
}

void motor_set_speed(int speed) {
    DACC->DACC_CDR = (/*0x1000 |*/ speed);
}

void motor_set_direction(int direction) {
    if (direction == 1) {
        PIOD->PIO_SODR |= PIO_SODR_P10; // motor direction (left?)
    } else {
        PIOD->PIO_CODR |= PIO_CODR_P10; // motor direction (right?)
    }
}