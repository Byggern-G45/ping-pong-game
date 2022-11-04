#include <sam.h>
#include <sam3x8e.h>
#include "../include/pwm.h"
//#include "uart.h"
//#include <utim>

int main(void) {
	//configure_uart();

	/* Initialize the SAM system */
	SystemInit();

	while (1)
	{
	}
}

void IR_init(){
	
}

bool goal_reg(){
	
}

void excercise7_blinkLED_init(){
	PIOA->PIO_OER |= 1<<20;
	PIOA->PIO_OER |= 1<<19;
	PIOA->PIO_PER |= 1<<20;
	PIOA->PIO_PER |= 1<<19;
}

void excercise7_blink_led(){
	PIOA->PIO_SODR |= 1<<20;
	PIOA->PIO_SODR |= 1<<19;
	delay(1000);
	PIOA->PIO_CODR |= 1<<20;
	PIOA->PIO_CODR |= 1<<19;
	delay(1000);
}
