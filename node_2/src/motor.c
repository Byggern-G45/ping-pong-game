/*
 * motor.c
 */ 

#include "../include/motor.h"
#include <stdio.h>
#include <sam.h>

void motor_init() {
    // Kok
    PMC->PMC_PCER0 |= PMC_PCER0_PID13; // Enable clock on PIOC-controller (??????????????)
	PMC->PMC_PCER1 |= PMC_PCER1_PID38; // DACC ID                         (??????????????)
	DACC->DACC_MR |= DACC_MR_TAG_EN;   // Tag selection mode
	DACC->DACC_CHER |= DACC_CHER_CH1;  // Enable DAC1 (CH1)
    //

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

void motor_set_speed(int speed) {
    if (speed < 0) {
        DACC->DACC_CDR = -speed;        // Set absolute value of speed
        PIOD->PIO_SODR |= PIO_SODR_P10; // Motor direction (left?)
    } else {
        DACC->DACC_CDR = speed;         // Set speed
        PIOD->PIO_CODR |= PIO_CODR_P10; // Motor direction (right?)
    }
}

int motor_read_position() {
    /*
    PIOD->PIO_CODR |= PIO_CODR_P0;  //set !OE low to enable output of encoder
	PIOD->PIO_CODR |= PIO_CODR_P2;  //Set SEL low to get high byte

    for (int i = 0; i < 400000; i++) {  //Wait for output to stabilize
        
    }

    int high_byte = PIOC->PIO_PDSR; //Read high byte
	PIOD->PIO_SODR |= PIO_SODR_P2;  //Set SEL high to get low byte

    for (int i = 0; i < 400000; i++) {
        
    }

    int low_byte = PIOC->PIO_PDSR;  //Read low byte
    PIOD->PIO_SODR |= PIO_SODR_P0;  //set !OE high to disable output of encoder

    int in_min = -296;   // Value of encoder when all the way to the left
    int in_max = -19236; // Value of encoder when all the way to the right
    int out_min = -100;
    int out_max = 100;

    int position = (high_byte << 8) | low_byte; //Combine high and low byte
    return low_byte; //(position - in_min)*(out_max - out_min)/(in_max - in_min) + out_min; // Map to [-100, 100]
    


    PIOD->PIO_CODR |= PIO_CODR_P0; //set !OE low to enable output of encoder
	PIOD->PIO_CODR |= PIO_CODR_P2; //Set SEL low to get high byte

	//vent 20micro s
	for (int i = 0; i<400000;i++){
        //asm("nop");
    }
	int MSB = PIOC->PIO_PDSR ;

	PIOD->PIO_SODR |= PIO_SODR_P2; //Set SEL high to get low byte

	//vent 20 micro s
	for (int i = 0; i<400000;i++){
        //asm("nop");
    }
	int LSB = PIOC->PIO_PDSR ;


	PIOD->PIO_SODR |= PIO_SODR_P0;

	int encoder_data = (LSB | (MSB<<8));
	//if(encoder_data>0){encoder_data=0;}
	//if (encoder_data<-17000){encoder_data=-16700;}

	//Convert from 0 to -17 000 to -100,100
	//int8_t data = (int8_t) ((encoder_data)*(-1)*296/19236 -100);
    //int data = (-encoder_data - 296) * (100 - -100) / (19236 - 296) + -100;
    // 9766 is middle

	return encoder_data;
    */
    
    PIOD->PIO_CODR |= PIO_CODR_P0; //set !OE low to enable output of encoder
	PIOD->PIO_CODR |= PIO_CODR_P2; //Set SEL low to get high byte

	//vent 20micro s
	for (uint16_t i = 0; i<4000;i++){}
	uint8_t MSB = PIOC->PIO_PDSR ;

	PIOD->PIO_SODR |= PIO_SODR_P2; //Set SEL high to get low byte

	//vent 20 micro s
	for (uint16_t i = 0; i<4000;i++){}
	uint8_t LSB = PIOC->PIO_PDSR ;


	PIOD->PIO_SODR |= PIO_SODR_P0;

	int16_t encoder_data = (LSB | (MSB<<8));
	//if(encoder_data>0){encoder_data=0;}
	//if (encoder_data<-17000){encoder_data=-16700;}

	//Convert from 0 to -17 000 to -100,100
	int8_t data = (int8_t) ((encoder_data)*(-1)*200/17000 -100);

	return encoder_data;
}