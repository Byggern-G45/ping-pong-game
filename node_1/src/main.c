#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_adc.h"
#include "../include/atmega162_oled.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf

void sram_test() {
	volatile char *ext_ram = (char *) 0x1800;
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrivial_errors = 0;
	printf("Starting SRAM test...\n");
	uint16_t seed = rand();
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++){
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value){
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++)
	{
		uint8_t some_value = rand();
		uint8_t retrived_value = ext_ram[i];
		if (retrived_value != some_value){
			printf("Retrievial phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retrived_value, some_value);
			retrivial_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrievial phase \n",write_errors,retrivial_errors);
}

int main() {
	fdevopen(usart_transmit, usart_receive); // Enable printf to JTAG
	usart_init();
	sram_init();
	sram_test();
	adc_init();
	
	
	while (1) {
		adc_start_conversion();
		printf("In main | 	x: %d		y: %d		button: %d\n", joystick.position[0], joystick.position[1], joystick_button_read());
    }
}