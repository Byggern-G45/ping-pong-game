#include "../include/IR_driver.h"

void ADC_init() {
    PMC -> PMC_PCER1 |= PMC_PCER1_PID37; //Enable clock for ADC
	ADC -> ADC_CHER |= ADC_CHER_CH0; 	 //Enable channel 0
	ADC -> ADC_MR |= ADC_MR_FREERUN_ON;  //Enable freerun so adc does not have to wait for trigger
	ADC -> ADC_CR |= ADC_CR_START; 		 //Start conversion

	PIOC->PIO_PER |= PIO_PER_P12; 		 //Enable PIO control of LED pin 51
	PIOC->PIO_OER |= PIO_OER_P12; 		 //Set LED pin 51 as output
	PIOC->PIO_SODR |= PIO_SODR_P12; 	 //Set solenoid pin 51 low
}

uint16_t get_IR_value() {
	return ADC -> ADC_CDR[0];
}

uint8_t get_ball_misses(uint8_t reset) {
	static uint8_t misses = 0;
	static uint16_t delay_counter = 0;
	if (reset) {
		misses = 0;
		delay_counter = 0;
		return 0;
	}

	//printf("misses: %d\n", misses); // The code does not work without this line. ´\(o_0)/`
	
	if (misses < 3) {
		PIOC->PIO_CODR |= PIO_CODR_P12; //Set LED pin 51 low
	} else {
		PIOC->PIO_SODR |= PIO_SODR_P12; //Set LED pin 51 high
	}

	if (delay_counter < 200) { // Give the system some slowness
		delay_counter++;
		return misses;
	}

	delay_counter = 0;

	uint16_t IR_value = get_IR_value();
	//printf("IR value: %d\n\r", IR_value);
	if (IR_value < 1000) { // ball detected
		misses++;
	}

	return misses;
}
