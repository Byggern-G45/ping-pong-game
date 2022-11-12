#include "sam.h"
#include <sam3x8e.h>
#include "../include/printf-stdarg.h"
#include "../include/uart.h"
#include "../include/can_controller.h"
#include "../include/can_interrupt.h"
#include "../include/pwm.h"
#include "../include/solenoid.h"
#include "../include/motor.h"
#include "../include/regulator.h"

#define BAUD_RATE_CAN 	125000UL
#define BAUD_RATE_UART 	9600UL
#define MCK 			84000000UL
//#define BRP 	 		(MCK/(16UL*BAUD_RATE_CAN) - 1)
//#define T_CSC           ((BRP + 1UL)⁄MCK)
//#define T_PRS		    (3*T_CSC)
//#define PROPAG          (T_PRS/T_CSC - 1)
//#define PHASE1          5

int main(void) {
	SystemInit();
	configure_uart();
	pwm_init();
	motor_init();
	solenoid_init();
	if (can_init_def_tx_rx_mb(0x00290561)) {
		printf("CAN init failed\n\r");
	}

	//convert_to_pwm(255);
	motor_set_speed(-1);
	
	
	while (1) {
		
		printf("Encoder: %d\n", motor_read_position());
		//__disable_irq();
		//printf("Position: %d\n", motor_read_position());
		//printf("ID: 	%d\t", msg_rx.id);
		//printf("Length: %d\t", msg_rx.data_length);
		//printf("Data: 	%d%d\10\13", msg_rx.data[0], msg_rx.data[1]);

		
		// convert_to_pwm(msg_rx.data[0]);
		//convert_to_pwm(msg_rx.data[0]);
		//__enable_irq();
	}
}
