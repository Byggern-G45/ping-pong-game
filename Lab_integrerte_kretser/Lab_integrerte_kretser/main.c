/*
 * Lab_integrerte_kretser.c
 *
 * Created: 9/2/2022 10:35:13 AM
 * Author : kelti
 */ 


#include "atmega162_usart.c"
#include <avr/io.h>
#include <stdio.h>
//fdevopen(unsigned char atmega162_usart_transmit(), unsigned char atmega162_usart_receive())
//#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	//DDRA = 0xFF;
	//DDRC = 0xFF;
	//DDRE = (1<<PE1);
	//PORTE = (1<<PE1);
	SFIOR = (1<<XMM2) | (0<<XMM1) | (0<<XMM0);
	MCUCR = (1<<SRE);
	
	
	fdevopen(atmega162_usart_transmit, atmega162_usart_receive);
	atmega162_usart_init();
	printf("Hello World");
	SRAM_test();
	//set_adress();
	while (1)
	{
		
		
		
	}
	
}


void Blink_Led(){
	PORTA = 0xff;
	_delay_ms(1000);
	PORTA = 0x00;
	_delay_ms(1000);
	};
	
void set_adress(){
	unsigned int adress = 0x0101;
	PORTC = 0b11111111;//(unsigned int)(adress>>8);              
	PORTA = 0xff;//(unsigned int)adress;
	
}



void SRAM_test ( void )
{
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
			printf("Write phase error: ext_ram[%4d] = %02X (sholud be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++)
	{
		uint8_t some_value = rand();
		uint8_t retrived_value = ext_ram[i];
		if (retrived_value != some_value){
			printf("Retrivial phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retrived_value, some_value);
			retrivial_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrivial phase \n",write_errors,retrivial_errors);
}