#include "sam.h"
#include <sam3x8e.h>
#include "../include/printf-stdarg.h"
#include "../include/uart.h"
#include "../include/can_controller.h"
#include "../include/can_interrupt.h"
#include "../include/pwm.h"
#include "../include/solenoid.h"
#include "../include/motor.h"

volatile int* test = 0;

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
	SystemInit();
	configure_uart();
	pwm_init();
	motor_init();
	solenoid_init();

	if (can_init_def_tx_rx_mb(0x00290561)) {
		printf("CAN init failed\n\r");
	}

	CAN_MESSAGE msg_rx;

	convert_to_pwm(255);
	motor_set_speed(100);
	
	
	while (1) {
		
		//__disable_irq();
		printf("Position: %d\n", motor_read_position());
		//printf("ID: 	%d\t", msg_rx.id);
		//printf("Length: %d\t", msg_rx.data_length);
		//printf("Data: 	%d%d\10\13", msg_rx.data[0], msg_rx.data[1]);

		
		// convert_to_pwm(msg_rx.data[0]);
		//convert_to_pwm(msg_rx.data[0]);
		//__enable_irq();
	}
}

void IR_init(){
	
}

uint8_t goal_reg(){
	
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
