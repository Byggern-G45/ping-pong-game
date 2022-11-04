#include "sam.h"
#include "../include/printf-stdarg.h"
#include "../include/uart.h"

#include "../include/can_controller.h"
#include "../include/can_interrupt.h"

#include <sam.h>
#include <sam3x8e.h>
#include "../include/pwm.h"
//#include "uart.h"
//#include <utim>

#define BAUD_RATE_CAN 	125000UL
#define BAUD_RATE_UART 	9600UL
#define MCK 			84000000UL
//#define BRP 	 		(MCK/(16UL*BAUD_RATE_CAN) - 1)
//#define T_CSC           ((BRP + 1UL)⁄MCK)
//#define T_PRS		    (3*T_CSC)
//#define PROPAG          (T_PRS/T_CSC - 1)
//#define PHASE1          5


int main(void) {
	/* Initialize the SAM system */
  //configure_uart();
	SystemInit();
	configure_uart();

	printf("PROGRAM STARTED\n\r");

	//(BRP << 16) | (1 << 9) | (1 << 8) | (1 << 2) | (1 << 1) | (1 << 0)
	// 0x00290165
	if (can_init_def_tx_rx_mb(0x00290561)) {
		printf("CAN init failed\n\r");
	}
	// can_send(CAN_MESSAGE* can_msg, uint8_t tx_mb_id);
	// can_receive(CAN_MESSAGE* can_msg, uint8_t rx_mb_id);

	//CAN_MESSAGE msg_rx;
	CAN_MESSAGE msg_tx;
	msg_tx.id = 0x0;
	msg_tx.data_length = 7;
	msg_tx.data[0] = 0x0;
	msg_tx.data[1] = 0x1;
	msg_tx.data[2] = 0x2;
	msg_tx.data[3] = 0x3;
	msg_tx.data[4] = 0x4;
	msg_tx.data[5] = 0x5;
	msg_tx.data[6] = 0x6;

	printf("%d\n", can_send(&msg_tx, 0));
	
	msg_tx.id = 0x0;
	msg_tx.data_length = 7;
	msg_tx.data[0] = 'H';
	msg_tx.data[1] = 'e';
	msg_tx.data[2] = 'l';
	msg_tx.data[3] = 'g';
	msg_tx.data[4] = 0x4;
	msg_tx.data[5] = 0x5;
	msg_tx.data[6] = 0x6;
	
	printf("%d\n", can_send(&msg_tx, 0));
	while (1) {
		

		//for (int i = 0; i < 1000000; i++) {
		//	__asm__("nop");
		//	printf("helg");
		//}

		// printf("Status: %d\t", can_receive(&msg_rx, 1));
		// printf("ID: 	%d\t", msg_rx.id);
		// printf("Length: %d\t", msg_rx.data_length);
		// printf("Data: 	%d%d%d%d%d%d%d%d\10\13", 
		// 	msg_rx.data[0], 
		// 	msg_rx.data[1], 
		// 	msg_rx.data[2], 
		// 	msg_rx.data[3], 
		// 	msg_rx.data[4], 
		// 	msg_rx.data[5], 
		// 	msg_rx.data[6], 
		// 	msg_rx.data[7]
		// );
		// CAN0_Handler();
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
