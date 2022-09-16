#include "../include/atmega162_usart.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf

int main() {	
	fdevopen(atmega162_usart_transmit, atmega162_usart_receive); // Enable printf to JTAG
	atmega162_usart_init();
	atmega162_sram_init();
	while (1) {

    }
}



void adc_init(){
	DDRD = (1 <<DDD4);
	
}

struct adc_read(int channels){
	struct{
		volatile uint8_t Analog_value[channels];
		}Analog_input;
	volatile char *ext_ram = (char *) 0x1400;
	ext_ram[0] = 0x00;
	for (uint8_t i = 0, i < channels, i++){
		PORTD = (0<<PD7);
		uint8_t byte = (uint8_t)(ext_ram[i]);
		Analog_input.Analog_value[i] = byte;
		printf("%b/n/r", byte);
		PORTD = (1<<PD7);
	};
}

/*
void adc_to_angle(uint8_t A0, uint8_t A1){
	
	int x = 
	int y =
}

