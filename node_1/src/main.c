#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_adc.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf

int main() {	
	fdevopen(atmega162_usart_transmit, atmega162_usart_receive); // Enable printf to JTAG
	atmega162_usart_init();
	atmega162_sram_init();
	atmega162_adc_init();
	printf("\n\r\n\rhello\n\r\n\r");
	
	while (1) {
		atmega162_adc_start_conversion();
		joystick.position = 
    }
}