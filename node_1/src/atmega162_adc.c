/* atmega162_adc.c -- See atmega162_adc.h for info */

#define ATMEGA162_ADC_IMPORT
#include "../include/atmega162_adc.h"

#define ADC_ADDRESS (volatile char*)0x1400

typedef enum direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

static volatile uint8_t conversion_done;
struct adc {
	volatile uint8_t position[2];
	volatile direction direction;
	volatile uint8_t correction[2];
}
struct adc joystick;
struct adc slider;

ISR(INT2_vect) {
	atmega162_joystick_read();
	conversion_done = 1;
}

void atmega162_adc_init() {
	DDRB |= (0<<DDB0);						 // Set PD2 as input for joystick button
	PORTB |= (1<<PORTB0);					 // Enable pull-up resistor for joystick button

	DDRD |= (1<<DDD4);					 		 // Set Clk as output
	TCCR3A |= (0<<COM3A1) | (1<<COM3A0)			 // Toggle on Compare Match.
	TCCR3A |= (1<<WGM30) | (1<<WGM31); 			 // PWM, Phase Correct
	TCCR3B |= (0<<WGM32) | (1<<WGM33);
	TCCR3B |= (0<<CS32) | (0<<CS31) | (1<<CS30); // No Clk prescaling	
	
	cli();								// Disable global interrupt to hinder unwanted interrupt
	//MCUCR |= (1<<ISC01) | (1<<ISC00);	// Activate INT0 on rising edge
	//MCUCR |= (1<<ISC11) | (1<<ISC10);	// Activate INT1 on rising edge
	//GICR |= (1<<INT0) | (1<<INT1);	// Enable INT0 and INT1								
	EMCUCR |= (1<<ISC2);				// Activate INT2 on rising edge
	GICR |= (1<<INT2);					// Enable INT2
	sei();								// Enable global interrupt

	conversion_done = 1;
	atmega162_joystick_calibrate();
}

void atmega162_joystick_calibrate() {
	atmega162_adc_start_conversion();
	while (conversion_done == 0);
	joystick.correction[0] = joystick.position[0];
	joystick.correction[1] = joystick.position[1];	
}

void atmega162_adc_start_conversion() {
	if (conversion_done) { // If conversion is done, start new conversion
		*ADC_ADDRESS = 0x0; 		// ADC is hardwired, so we do not care about the value
		conversion_done = 0;
	}	
}

void atmega162_adc_read() {
	joystick.position[0] = (uint8_t)(*ADC_ADDRESS);	// Read ch0 joystick x position
	joystick.position[1] = (uint8_t)(*ADC_ADDRESS); // Read ch1 joystock y position
	slider.position[0] = (uint8_t)(*ADC_ADDRESS); 	// Read ch2
	slider.position[1] = (uint8_t)(*ADC_ADDRESS); 	// Read ch3
	joystick.position[0] -= joystick.correction[0];	// Subtract correction
	joystick.position[1] -= joystick.correction[1];	// Subtract correction
}

uint8_t to_percentage(uint8_t byte) {
    return byte*100/255;
}

uint8_t atmega162_joystick_button_read() {
	return (PINB & (1<<PB0)); // Return 1 if button is pressed, 0 if not
}

/*
void adc_to_angle(uint8_t A0, uint8_t A1){
	
	int x = 
	int y =
}
*/