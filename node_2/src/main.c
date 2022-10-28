#include <sam.h>
#include "../include/printf-stdarg.h"
#include "../include/uart.h"

#include "../include/can_controller.h"
#include "../include/can_interrupt.h"

#define BAUD_RATE_CAN 	9600UL
#define BAUD_RATE_UART 	9600UL
#define MCK 			64000000UL
//#define BRP 	 		(MCK/(16UL*BAUD_RATE_CAN) - 1)
// t_CSC = (BRP + 1)⁄MCK

int main(void) {
	/* Initialize the SAM system */
	SystemInit();
	PIOA->PIO_OER = 1<<20;
	PIOA->PIO_OER = 1<<19;
	PIOA->PIO_PER = 1<<0;
	PIOA->PIO_PER = 1<<1;
	//PIOA->PIO_SODR = 1<<19;
	PIOA->PIO_CODR = 0xffffffff;


	configure_uart();

	printf("Hello World!");

	can_init_def_tx_rx_mb(BAUD_RATE_CAN);
	// can_send(CAN_MESSAGE* can_msg, uint8_t tx_mb_id);
	// can_receive(CAN_MESSAGE* can_msg, uint8_t rx_mb_id);
	while (1) {
		PIOA->PIO_SODR = 1<<20;
		//PIOA->PIO_CODR = 0x1u<<20;
	}
}
