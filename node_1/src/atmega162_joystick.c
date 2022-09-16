/* atmega162_sram.c -- See atmega162_sram.h for info */

#define ATMEGA162_JOYSTICK_IMPORT
#include "../include/atmega162_joystick.h"

ISR(INT0_vect) {}
ISR(INT1_vect) {}
// ISR(INT2_vect) {}

void atmega162_joystick_init() {
	cli();								// Disable global interrupt to hinder unwanted interrupt
	MCUCR |= (1<<ISC01) | (1<<ISC00);	// Activate INT0 on rising edge
	MCUCR |= (1<<ISC11) | (1<<ISC10);	// Activate INT1 on rising edge
	GICR |= (1<<INT0) | (1<<INT1);		// Enable INT0 and INT1
	sei();								// Enable global interrupt
	/* INT2
	EMCUCR |= (1<<ISC2);	// Activate INT2 on rising edge
	GICR |= (1<<INT2);		// Enable INT2
	*/
}

void atmega162_joystick_start_conversion() {}

uint8_t atmega162_joystick_read() {}