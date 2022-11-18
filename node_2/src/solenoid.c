#define _IMPORT
#include "sam.h"
#include "sam3x8e.h"
#include "../include/solenoid.h"

void solenoid_init(){
	PIOC->PIO_PER |= PIO_PER_P13; //Enable PIO control of solenoid pin
	PIOC->PIO_OER |= PIO_OER_P13; //Set solenoid pin as output
	PIOC->PIO_SODR |= PIO_SODR_P13; //Set solenoid pin low
}


void solenoid(uint8_t input){
    static uint8_t solenoid_activated = 0;
	static uint8_t counter = 0;
	counter++;
	if (solenoid_activated && (counter > 20)) {
		PIOC->PIO_CODR |= PIO_CODR_P13; //Set solenoid pin low
		counter = 0;
		//printf("Counter\n\r");
	} else if(input == 1) {
		solenoid_activated = 0;
		counter = 0;
		//printf("Solenoid deactivated\n\r");
	} 
	
	if ((input == 0) && (solenoid_activated == 0)) {
		PIOC->PIO_SODR |= PIO_SODR_P13; //Set solenoid pin high
		solenoid_activated = 1;
		counter++;
		//printf("Solenoid activated\n\r");
	}
	
}