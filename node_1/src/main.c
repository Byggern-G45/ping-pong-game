#include "../include/atmega162_usart.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf

int main() {	
	// fdevopen(atmega162_usart_transmit, atmega162_usart_receive); // Enable printf to JTAG
	atmega162_usart_init();
	atmega162_sram_init();
	while (1) {

    }
}

