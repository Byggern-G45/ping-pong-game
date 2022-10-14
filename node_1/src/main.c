#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_adc.h"
#include "../include/atmega162_oled.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf

int main() {
	fdevopen(usart_transmit, usart_receive); // Enable printf to JTAG
	usart_init();
	sram_init();
	adc_init();
	
	
	while (1) {
		adc_start_conversion();
		printf("In main | 	x: %d		y: %d		button: %d\n", joystick.position[0], joystick.position[1], joystick_button_read());
    }
}