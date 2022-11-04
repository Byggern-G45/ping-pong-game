#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_adc.h"
#include "../include/atmega162_oled.h"
#include "../include/atmega162_mcp2515.h"
#include "../include/atmega162_spi.h"
#include "../include/atmega162_can.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf
#include <util/delay.h>
#define  F_CPU 4000000UL





int main() {	
	fdevopen(usart_transmit, usart_receive); // Enable printf to JTAG
	usart_init();
	can_init();
	sram_init();
	adc_init();
	
	// can_message_t rx_msg;
	// can_message_t tx_msg;
	



	// can_message_psend(&tx_msg);

	// printf("%x \n", mcp_read(0x0e));
	// printf("%x \n", mcp_read(0x0f));

	// printf("\n\n+n########################################\n");
	// printf("SENT ID:    	%x\n", tx_msg.id);
	// printf("SENT LENGTH:	%d\n", tx_msg.length);
	// printf("SENT DATA:  	");
	// for (uint8_t i = 0; i < tx_msg.length; i++) {
	// 	printf("%d	", tx_msg.data[i]);
	// }
	// printf("\n");
	// printf("\n########################################\n");


	// rx_msg = can_message_receive();

	// printf("\n########################################\n");
	// printf("RECEIVED ID:    %x\n", rx_msg.id);
	// printf("RECEIVED LENGTH:%d\n", rx_msg.length);
	// printf("RECEIVED DATA:  ");
	// for (uint8_t i = 0; i < rx_msg.length; i++) {
	// 	printf("%x", rx_msg.data[i]);
	// }
	// printf("\n");
	// printf("\n########################################\n");






	
	
	while (1){

		//_delay_ms(100);

		adc_start_conversion();
		can_message_t tx_msg;
		// can_message_t rx_msg;

	tx_msg.id = 0x7ff;
	tx_msg.length = 2;
	tx_msg.data[0] = joystick.position[0];
	tx_msg.data[1] = joystick.position[1];


	can_message_psend(&tx_msg);




		
		//rx_msg = can_message_receive();

	 //printf("\n########################################\n");
	// printf("%x \n", mcp_read(0x0e));
	// mcp_read_rx_status();
	// printf("RECEIVED ID:    %x\n", rx_msg.id);
	// printf("RECEIVED LENGTH:%d\n", rx_msg.length);
	// printf("RECEIVED DATA:  ");
	// for (uint8_t i = 0; i < rx_msg.length; i++) {
	// 	printf("%d		", rx_msg.data[i]);
	// }
	// printf("\n");
	// printf("\n########################################\n");
	
    }
}