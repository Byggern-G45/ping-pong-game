#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_adc.h"
#include "../include/atmega162_oled.h"
#include "../include/atmega162_mcp2515.h"
#include "../include/atmega162_spi.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf



int main() {	
	fdevopen(usart_transmit, usart_receive); // Enable printf to JTAG
	usart_init();
	// atmega162_sram_init();
	// atmega162_joystick_init();
	printf("\n\r\n\rhello\n\r\n\r");
	printf("SPI_init\n\r");
	SPI_init();
	printf("SPI_INITED\n\r");
	printf("MPC2515_INITED\n\r");
	mcp2515_init();
	printf("MPC2515_DONE\n\r");
	
	
	// while (1) {
	// 	atmega162_joystick_start_conversion();
    // }
}
