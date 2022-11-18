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



void menu(menu_state){
	switch (menu_state)
	{
	case NEUTRAL:
		oled_home();
		oled_print("-> SRAM test      ");
		oled_pos(1,0);
		oled_print("   ADC test      ");
		oled_pos(2,0);
		oled_print("   CAN test    ");
		oled_pos(3,0);
		oled_print("   Start game    ");
		oled_pos(4, 0);
		oled_print("   Print helg   ");
		uint8_t button = joystick_button_read();
		if (button == 0) {
			oled_reset();
			oled_print("Testing SRAM...");
			uint8_t errors = sram_test();
			oled_pos(1,0);
			if (errors == 0 ){
			oled_print("0 errors");
			}
			else if (errors < 1000){
				oled_print("1000 > errors");
			}
			else {
				oled_print("1000 < errors");
			}
			
			oled_pos(2,0);
			oled_print("detected");
			_delay_ms(30000);
			oled_reset();	
		}
		break;
	case UP:
		oled_home();
		oled_print("   SRAM test  ");
		oled_pos(1,0);
		oled_print("-> ADC test  ");
		oled_pos(2,0);
		oled_print("   CAN test  ");
		oled_pos(3,0);
		oled_print("   Start game  ");
		button = joystick_button_read();
		if (button == 0) {
			oled_reset();
			oled_print("ADC test...");
			oled_pos(1,0);
			oled_print("Doing nothing :)");
			_delay_ms(30000);
			oled_reset();
		}
		break;
	case RIGHT:
		oled_home();
		oled_print("   SRAM test  ");
		oled_pos(1, 0);
		oled_print("   ADC test   ");
		oled_pos(2, 0);
		oled_print("-> CAN test   ");
		oled_pos(3, 0);
		oled_print("   Start game   ");
		oled_pos(4, 0);
		oled_print("   Print helg   ");
		button = joystick_button_read();
		if (button == 0) {
			oled_reset();
			oled_print("CAN test...");
			oled_pos(1,0);
			oled_print("Doing nothing :)");
			_delay_ms(30000);
			oled_reset();
		}
		break;
	case DOWN:
		
		oled_home();
		oled_print("   SRAM test"  );
		oled_pos(1,0);
		oled_print("   ADC test"  );
		oled_pos(2,0);
		oled_print("   CAN test"  );
		oled_pos(3,0);
		oled_print("-> Start game"  );
		oled_pos(4, 0);
		oled_print("   Print helg   ");
		button = joystick_button_read();
		if (button == 0) {
			oled_reset();
			oled_print("Starting game...");
			oled_pos(1,0);
			oled_print("Joystick bound");
			oled_pos(2,0);
			oled_print("to game");
			flip_bit = 1;
			while(flip_bit){
			adc_start_conversion();
			button = joystick_button_read();
			can_message_t tx_msg;

			tx_msg.id = 0x7ff;
			tx_msg.length = 4;
			tx_msg.data[0] = joystick.position[0];
			tx_msg.data[1] = joystick.position[1];
			tx_msg.data[2] = button;
			tx_msg.data[3] = 0;

			can_message_psend(&tx_msg);
			}
			for (uint8_t i = 0; i < 20; i++) {
			can_message_t tx_msg;

			tx_msg.id = 0x7ff;
			tx_msg.length = 4;
			tx_msg.data[0] = joystick.position[0];
			tx_msg.data[1] = joystick.position[1];
			tx_msg.data[2] = button;
			tx_msg.data[3] = 1;

			can_message_psend(&tx_msg);
			}
		}
		break;
	case LEFT:
		oled_home();
		oled_print("   SRAM test  ");
		oled_pos(1, 0);
		oled_print("   ADC test   ");
		oled_pos(2, 0);
		oled_print("   CAN test   ");
		oled_pos(3, 0);
		oled_print("   Start game   ");
		oled_pos(4, 0);
		oled_print("-> Print helg   ");
		button = joystick_button_read();
		if (button == 0) {
			oled_reset();
			oled_print("# # ### #    ##");
			oled_pos(1,0);
			oled_print("# # #   #   #  ");
			oled_pos(2,0);
			oled_print("# # #   #  #   ");
			oled_pos(3,0);
			oled_print("### ### #  # ##");
			oled_pos(4,0);
			oled_print("# # #   #  #  #");
			oled_pos(5,0);
			oled_print("# # #   #   # #");
			oled_pos(6,0);
			oled_print("# # #   #   # #");
			oled_pos(7,0);
			oled_print("# # ### ###  ##");
			_delay_ms(30000);
			oled_reset();
		}
		break;

	default:
		break;
	}
}

int main() {	
	fdevopen(usart_transmit, usart_receive); // Enable printf to JTAG
	usart_init();
	can_init();
	sram_init();
	oled_init();
	adc_init();







	
	
	while (1){
		menu(joystick.direction);
		adc_start_conversion();






		
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




	