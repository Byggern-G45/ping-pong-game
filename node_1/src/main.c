#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_joystick.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf

int main() {	
	// fdevopen(atmega162_usart_transmit, atmega162_usart_receive); // Enable printf to JTAG
	atmega162_usart_init();
	atmega162_sram_init();
	atmega162_joystick_init();
	while (1) {

    }
}

