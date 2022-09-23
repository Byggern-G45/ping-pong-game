/* atmega162_sram.c -- See atmega162_sram.h for info */

#define ATMEGA162_JOYSTICK_IMPORT
#include "../include/atmega162_joystick.h"

#define ADC_START_ADDRESS (volatile char*)0x1400
//volatile char* ADC_START_ADDRESS = 0x1400;
#define ATMEGA162_JOYSTICK_CHANNELS 4

uint8_t temp;

struct{
	volatile uint8_t position[ATMEGA162_JOYSTICK_CHANNELS];
	volatile uint8_t conversion_done;
} joystick;

ISR(INT2_vect) {
	atmega162_joystick_read();
	joystick.conversion_done = 1;
}

ISR(INT1_vect) {}
// ISR(INT2_vect) {}

void atmega162_joystick_init() {
	joystick.conversion_done = 1;
	DDRD |= (1<<DDD4);					// Set Clk as output
	DDRD = (1 << PD4);
	TCCR3A|=(1<<WGM30)|(1<<WGM31)|(1<<COM3A0)|(1<<CS30);
	//TCCR3A |= (1<<COM3A0) | (1<<WGM30);
	TCCR3B |= (1<<WGM33) | (1<<CS30);
	
	cli();								// Disable global interrupt to hinder unwanted interrupt
	/*
	MCUCR |= (1<<ISC01) | (1<<ISC00);	// Activate INT0 on rising edge
	MCUCR |= (1<<ISC11) | (1<<ISC10);	// Activate INT1 on rising edge
	GICR |= (1<<INT0) | (1<<INT1);		// Enable INT0 and INT1
	sei();								// Enable global interrupt
	*/
	EMCUCR |= (1<<ISC2);	// Activate INT2 on rising edge
	GICR |= (1<<INT2);		// Enable INT2
	sei();
}

void atmega162_joystick_start_conversion() {
	if (joystick.conversion_done) {
		*ADC_START_ADDRESS = 0x0;
		joystick.conversion_done = 0;
	}
	
}

void atmega162_joystick_read() {
	if (PD7 == 1 && temp == 0){
		//PORTD = (0<<PD7);
		uint8_t byte = (uint8_t)(*ADC_START_ADDRESS);
		joystick.position[0] = byte;
		printf("%d: %d\n", 0, byte);
		temp = 1;
		
		//PORTD = (1<<PD7);
	}
	else if (PD7 == 0 && temp == 1){
		temp = 0;
		printf("Wrong state");
		atmega162_joystick_read();
	}
	else {
		printf("Wrong state\n, %d", PD7);
		atmega162_joystick_read();
	}
}

/*
void adc_to_angle(uint8_t A0, uint8_t A1){
	
	int x = 
	int y =
}
*/