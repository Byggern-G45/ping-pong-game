#include "sam.h"
#include <sam3x8e.h>
#include "../include/printf-stdarg.h"
#include "../include/uart.h"
#include "../include/can_controller.h"
#include "../include/can_interrupt.h"
#include "../include/pwm.h"
#include "../include/timer.h"
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
	//timer_init();
	
	if (can_init_def_tx_rx_mb(0x00290561)) {
		printf("CAN init failed\n\r");
	}
	
	
	while (1) {
		regulate();
	}
}

/** 
 *  -------------------------------------
 * |                                     |
 * | White  Purple  Green  Orange  Brown |
 * |                                     |
 * | Black  Gray    Blue   Yellow  Red   |
 * |                                     |
 *  -------------,       ,---------------
 *               --------
 *                  ))
 *                 ((
 * 				    ))
 * 				   ((
 * 				    ))
 * 				   ((
 * 					))
 *  -------------------------------------
 * |                                     |
 * | sol     sol     nc     ir+   photo+ |
 * |                                     |
 * | srvsig  srv5v  srvgnd  ir-   photo- |
 * | 								     |
 *  -------------,       ,---------------
 *               --------             
 */
