/* atmega162_adc.c -- See atmega162_adc.h for info */

#define ATMEGA162_ADC_IMPORT
#include "../include/atmega162_adc.h"

#define ADC_ADDRESS (volatile char*)0x1400

static volatile uint8_t conversion_done;

/**
 * @brief Interrupt service routine for ADC conversion complete.
 * 	  	  Triggers on rising edge of READY signal.
 */
ISR(INT2_vect) {
	
	
}

/**
 * @brief Interrupt service routine for left(?) button press.
 * 		  Triggers on rising edge of PB0.
 */
ISR(INT1_vect) {
	_adc_read();
	printf("In ISR | 	x: %d		y: %d		s: %d		b: %d		button: %d		direction: %d\n", joystick.position[0], joystick.position[1], left_slider.position, right_slider.position, joystick_button_read(), joystick.direction);
	_calculate_direction();
	conversion_done = 1;
	
	
}

/**
 * @brief Interrupt service routine for right(?) button press.
 * 		  Triggers on rising edge of PB1.
 */
ISR(INT0_vect) {

}

void adc_init() {
	DDRB |= (0<<DDB0);						 // Set PD2 as input for joystick button
	PORTB |= (1<<PORTB0);					 // Enable pull-up resistor for joystick button

	DDRD |= (1<<DDD4);					 	 // Set Clk as output
	TCCR3A |= (0<<COM3A1) | (1<<COM3A0);	 // Toggle on Compare Match.
	TCCR3A |= (1<<WGM30) | (1<<WGM31); 	 	 // PWM, Phase Correct
	TCCR3B |= (0<<WGM32) | (1<<WGM33);
	TCCR3B |= (0<<CS32) | (0<<CS31) | (1<<CS30); // No Clk prescaling	
	
	cli();								// Disable global interrupt to hinder unwanted interrupt
	MCUCR |= (1<<ISC01) | (1<<ISC00);	// Activate INT0 on rising edge
	MCUCR |= (1<<ISC11) | (1<<ISC10);	// Activate INT1 on rising edge
	GICR |= (1<<INT0) | (1<<INT1);		// Enable INT0 and INT1			
	EMCUCR |= (1<<ISC2);				// Activate INT2 on rising edge
	GICR |= (1<<INT2);					// Enable INT2
	sei();								// Enable global interrupt

	conversion_done = 1;
	_joystick_calibrate();
}

void _joystick_calibrate() {
	adc_start_conversion();
	printf("Calibrating joystick");
	while (conversion_done == 0) printf(".");
	joystick.correction[0] = joystick.position[0] - 128;
	joystick.correction[1] = joystick.position[1] - 128;
}

void adc_start_conversion() {
	if (conversion_done) { 	// If conversion is done, start new conversion
		volatile char *ext_ram = (char *) 0x1400;
		ext_ram[0] = 0x00;
		conversion_done = 0;
	}	
}

void _adc_read() {
	volatile char *ext_ram = (char *) 0x1400;
	joystick.position[0] = ext_ram[1];	 		 // Read ch0 joystick x position
	joystick.position[1] = ext_ram[2];  			 // Read ch1 joystock y position
	left_slider.position = ext_ram[3];  // Read ch2 slider 1 position
	right_slider.position = ext_ram[4]; // Read ch3 slider 2 position

	/*if (0 < x && x < joystick.correction[0]) {
		joystick.position[0] = 0;					 // If x is within the deadzone, set to 0
	} else { 
		joystick.position[0] = x;
	}
	if (0 < y && y < joystick.correction[1]) {
		joystick.position[1] = 0;	 				 // If y is within the deadzone, set to 0
	} else {
		joystick.position[1] = y;
	}
	*/
}

void _calculate_direction() {
	uint8_t const MARGIN = 50;
	uint8_t x = _to_percentage(joystick.position[0]);
	uint8_t y = _to_percentage(joystick.position[1]);
	uint8_t is_horizontal = (y < MARGIN) && (y > -MARGIN);
	uint8_t is_vertical = (x < MARGIN) && (x > -MARGIN);
	if ((y > MARGIN) && is_vertical) {
		joystick.direction = UP;
	} else if ((y < -MARGIN) && is_vertical) {
		joystick.direction = DOWN;
	} else if ((x > MARGIN) && is_horizontal) {
		joystick.direction = RIGHT;
	} else if ((x < -MARGIN) && is_horizontal) {
		joystick.direction = LEFT;
	} else {
		joystick.direction = NEUTRAL;
	}
}

int8_t _to_percentage(uint8_t byte) {
    return byte*200/255 - 100; // Maps 0-255 to -100-100
}

uint8_t joystick_button_read() {
	return (PINB & (1<<PB0)); // Return 1 if button is pressed, 0 if not
}
