#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_adc.h"
#include "../include/atmega162_oled.h"
#include "../include/atmega162_mcp2515.h"
#include "../include/atmega162_spi.h"
#include "../include/atmega162_can.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf



int main() {	
	fdevopen(usart_transmit, usart_receive); // Enable printf to JTAG
	usart_init();
	can_init();
	
	can_message_t tx_msg;
	can_message_t rx_msg;

	tx_msg.id = 0x7ff;
	tx_msg.length = 6;
	tx_msg.data[0] = 'H';
	tx_msg.data[1] = 'e';
	tx_msg.data[2] = 'l';
	tx_msg.data[3] = 'l';
	tx_msg.data[4] = 'o';
	tx_msg.data[5] = '\0';
	
	can_message_send(&tx_msg);

	printf("\n\n");
	printf("CTRL:			%x\n", mcp_read(TXB0REG - 1));
	printf("STORED ID:      %x%x\n", mcp_read(TXB0REG) << 3, mcp_read(TXB0REG + 1) >> 5);
    printf("STORED LENGTH:  %d\n", mcp_read(TXB0REG + 4));
    printf("STORED DATA:    ");
    for (uint8_t i = 0; i < tx_msg.length; i++) {
        printf("%c", mcp_read(TXB0REG + 5 + i));
    }  
    printf("\n\n");

	
	rx_msg = can_message_receive();

	printf("RECEIVED ID:    %x\n", rx_msg.id);
	printf("RECEIVED LENGTH:%d\n", rx_msg.length);
	printf("RECEIVED DATA:  ");
	for (uint8_t i = 0; i < rx_msg.length; i++) {
		printf("%c", rx_msg.data[i]);
	}
	printf("\n\n");
	
	
	while (1); 
	// 	atmega162_joystick_start_conversion();
    // }
}
