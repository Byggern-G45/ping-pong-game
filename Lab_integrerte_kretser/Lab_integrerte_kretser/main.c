/*
 * Lab_integrerte_kretser.c
 *
 * Created: 9/2/2022 10:35:13 AM
 * Author : kelti
 */ 
//#ifndef F_CPU
//#define F_CPU 16000000UL // 16 MHz clock speed
//#endif


#define FOSC 4915200UL// Clock Speed
#define BAUD 9600UL
#define Pre_scaler 16UL
#define MYUBRR FOSC/(16UL*BAUD)-1UL

#include "atmega162_usart.c"
#include <avr/io.h>
//#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	USART_Init ( MYUBRR );
	while(1){
	USART_Transmit(66);
	//Blink_Led();
	}
}


void Blink_Led(){
	PORTA = 0xff;
	_delay_ms(1000);
	PORTA = 0x00;
	_delay_ms(1000);
	};

void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}
void USART_Transmit( unsigned int data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) 
	);
	
	/* Copy 9th bit to TXB8 */
	UCSR0B &= ~(1<<TXB80);
	if ( data & 0x0100 )
	UCSR0B |= (1<<TXB80);
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

