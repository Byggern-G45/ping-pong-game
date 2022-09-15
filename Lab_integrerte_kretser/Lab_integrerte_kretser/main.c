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
//#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	atmega162_usart_init();
	while(1){
	 atmega162_usart_transmit(65); //sends character
	//Blink_Led();
	}
}


void Blink_Led(){
	PORTA = 0xff;
	_delay_ms(1000);
	PORTA = 0x00;
	_delay_ms(1000);
	};



