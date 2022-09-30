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
	printf("\n\r\n\rhello\n\r\n\r");
	
	
	while (1) {
		adc_start_conversion();
    }
}