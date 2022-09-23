/* atmega162_sram.c -- See atmega162_sram.h for info */

#define ATMEGA162_JOYSTICK_IMPORT
#include "../include/atmega162_joystick.h"
//#include "util/delay.h"
//#define F_CPU 49000000000

#define ADC_START_ADDRESS (volatile char*)0x1400
//volatile char* ADC_START_ADDRESS = 0x1400;
#define ATMEGA162_JOYSTICK_CHANNELS 4

struct{
	volatile uint8_t position[ATMEGA162_JOYSTICK_CHANNELS];
	volatile uint8_t conversion_done;
}joystick;

ISR(INT2_vect) {
	atmega162_joystick_read();
	joystick.conversion_done = 1;
}

ISR(INT1_vect) {
	for (uint8_t i =0; i<=254;i++)
	{
		printf("HELG!\n");
	}
	
}
ISR(INT0_vect) {
	for (uint8_t i =0; i<=254;i++)
	{
		printf("TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!TISS!\n");
	}
	
}



// ISR(INT2_vect) {}

void atmega162_joystick_init() {
	joystick.conversion_done = 1;
	DDRD |= (1<<DDD4);					// Set Clk as output
	DDRD = (1 << PD4);
	TCCR3A|=(1<<WGM30)|(1<<WGM31)|(1<<COM3A0)|(1<<CS30);
	//TCCR3A |= (1<<COM3A0) | (1<<WGM30);
	TCCR3B |= (1<<WGM33) | (1<<CS30);
	
	cli();								// Disable global interrupt to hinder unwanted interrupt
	
	MCUCR |= (1<<ISC01) | (1<<ISC00);	// Activate INT0 on rising edge
	MCUCR |= (1<<ISC11) | (1<<ISC10);	// Activate INT1 on rising edge
	GICR |= (1<<INT0) | (1<<INT1);		// Enable INT0 and INT1
	sei();								// Enable global interrupt
	
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
	for (uint8_t i = 0; i < ATMEGA162_JOYSTICK_CHANNELS; i++){
		uint8_t byte = (uint8_t)(*ADC_START_ADDRESS);
		joystick.position[i] = byte;
		}
	printf("Posisjon x = %d, y = %d, z = %d, # = %d\n", joystick.position[0]*100/255,joystick.position[1],joystick.position[2],joystick.position[3]);
	
		//_delay_us(10);
		//PORTD = (1<<PD7);
}

/*
void adc_to_angle(uint8_t A0, uint8_t A1){
	
	int x = 
	int y =
}
*/