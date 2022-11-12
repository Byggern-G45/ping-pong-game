/*
 * motor.c
 */ 

#include "../include/motor.h"

void motor_init() {
    PMC->PMC_PCER0 |= PMC_PCER0_PID13; // Enable clock to bus on PIOC
	PMC->PMC_PCER1 |= PMC_PCER1_PID38; // Enable clock to use DACC
	DACC->DACC_MR |= DACC_MR_TAG_EN;   // Tag selection mode
	DACC->DACC_CHER |= DACC_CHER_CH1;  // Enable DAC1 (CH1)

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
	PIOD->PIO_SODR |= PIO_SODR_P1;  // Disable reset encoder
    PIOD->PIO_CODR |= PIO_CODR_P0;  // Enable encoder
}

void motor_set_speed(int16_t speed) {
    if (speed < 0) {
        speed = -speed;                 // Absolute value
        PIOD->PIO_SODR |= PIO_SODR_P10; // Motor direction left
    } else {
        PIOD->PIO_CODR |= PIO_CODR_P10; // Motor direction right
    }
    DACC->DACC_CDR = (speed - IN_SPEED_MIN)*(OUT_SPEED_MAX - OUT_SPEED_MIN)/
                     (IN_SPEED_MAX - IN_SPEED_MIN) + OUT_SPEED_MIN; // Map speed
}

int8_t motor_read_position() {
    PIOD->PIO_CODR |= PIO_CODR_P0;  // !OE low to enable encoder

	PIOD->PIO_CODR |= PIO_CODR_P2;                  // SEL low to get high byte
    for (uint16_t i = 0; i < 1000; i++) asm("nop"); // Need this delay to get correct value
    uint8_t high_byte = PIOC->PIO_PDSR;             // Get high byte

	PIOD->PIO_SODR |= PIO_SODR_P2;                  // SEL high to get low byte
    for (uint16_t i = 0; i < 1000; i++) asm("nop"); // Need this delay to get correct value
    uint8_t low_byte = PIOC->PIO_PDSR;              // Get low byte

    PIOD->PIO_SODR |= PIO_SODR_P0;  // !OE high to disable encoder

    uint16_t position = (high_byte << 8) | low_byte;
    return (position - IN_ENCODER_MIN)*(OUT_ENCODER_MAX - OUT_ENCODER_MIN)/
           (IN_ENCODER_MAX - IN_ENCODER_MIN) + OUT_ENCODER_MIN; // Map position
}