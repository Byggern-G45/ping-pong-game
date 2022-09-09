/*
 * Lab_integrerte_kretser.c
 *
 * Created: 9/2/2022 10:35:13 AM
 * Author : kelti
 */ 
//#ifndef F_CPU
//#define F_CPU 16000000UL // 16 MHz clock speed
//#endif


//#define FOSC 4915200UL// Clock Speed
//#define BAUD 9600UL
//#define Pre_scaler 16UL
//#define UBRR 31

#include "atmega162_usart.c"
#include <avr/io.h>
#include <stdio.h>
//fdevopen(unsigned char atmega162_usart_transmit(), unsigned char atmega162_usart_receive())
//#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	fdevopen(atmega162_usart_transmit, atmega162_usart_receive);
	atmega162_usart_init();
	printf("Hello World");
	while (1)
	{
		unsigned char byte = atmega162_usart_receive();
		if (byte) {
			atmega162_usart_transmit(byte);
			atmega162_usart_transmit(byte);
			atmega162_usart_transmit(byte);
			atmega162_usart_transmit(byte);
			atmega162_usart_transmit(byte);
		}
	}
	
}


void Blink_Led(){
	PORTA = 0xff;
	_delay_ms(1000);
	PORTA = 0x00;
	_delay_ms(1000);
	};



