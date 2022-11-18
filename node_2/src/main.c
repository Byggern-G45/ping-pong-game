#include "sam.h"
#include "../include/printf-stdarg.h"
#include "../include/uart.h"
#include <sam3x8e.h>
#include "../include/IR_driver.h"

#define BAUD_RATE_UART 9600UL
#define MCK 84000000UL

int main(void){
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	ADC_init();


    while (1){
		uint16_t IR_value = get_IR_value();
		printf("IR value = %d\n", IR_value);
	}
}


/*void excercise7_blinkLED_init(){
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
}*/
