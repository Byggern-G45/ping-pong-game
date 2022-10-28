/*
 * node_2.c
 *
 * Created: 21.10.2022 13:09:21
 * Author : birge
 */ 

#include "sam.h"
#include "uart.h"

int main(void)
{
	configure_uart();
	/* Initialize the SAM system */
	SystemInit();
	
	PIOA->PIO_PER |= (1 << 21); // enable IO
	PIOA->PIO_OER |= (1 << 21); // set as output
	PIOA->PIO_PUDR |= (1 << 21); // disable internal pull-up
	PIOA->PIO_OWER |= (1 << 21); // enable output write

	/* Replace with your application code */
	while (1) {
		PIOA->PIO_ODSR |= (1 << 21); // make pin HIGH
		delay(500);
		PIOA->PIO_ODSR &= ~(1 << 21); // make pin LOW
		delay(500);
	}
}
