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

void menu(menu_state) {
	switch (menu_state) // Switch statment for simple menu
	{
	case NEUTRAL: // Sram test state, prints menu options with arrow on selected option
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
		uint8_t button = joystick_button_read(); // Reads joystick button
		if (button == 0) { // If button is pressed
			oled_reset(); // Clear screen
			oled_print("Testing SRAM..."); // Print message
			uint8_t errors = sram_test(); // Run sram test
			oled_pos(1,0); // Go to next line
			if (errors == 0 ) { // If no errors
			 oled_print("0 errors"); // Print message 0 errors
			} else if (errors < 1000) { // If less than 1000 errors
				oled_print("1000 > errors"); // Print message 1000 > errors
			} else { // If more than 1000 errors
				oled_print("1000 < errors"); // Print message 1000 < errors
			}
			
			oled_pos(2,0); // Go to next line
			oled_print("detected"); // Print message detected
			_delay_ms(30000); // Wait 30 seconds--not realy 30 sekonds, about 5 secounds in real life due to wrong clk definition
			oled_reset();	// Clear screen
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
			flip_bit = 1; // Set flip bit to 1, this will start the game
			while(flip_bit) { // While flip bit is 1, interrupt will set it to 0
				adc_start_conversion(); // Start adc conversion
				button = joystick_button_read(); // Read joystick button
				can_message_t tx_msg; // Create can message

				tx_msg.id = 0x7ff; // Set id to 0x7ff
				tx_msg.length = 4; // Set length to 4
				tx_msg.data[0] = joystick.position[0]; // Set data[0] to joystick position x
				tx_msg.data[1] = joystick.position[1]; // Set data[1] to joystick position y
				tx_msg.data[2] = button; // Set data[2] to joystick button
				tx_msg.data[3] = 0; // Set data[3] to 0 used for signaling if game is over

				can_message_psend(&tx_msg); // Send can message
			}
			for (uint8_t i = 0; i < 20; i++) { // For loop to send 20 messages in case of lost messages
				can_message_t tx_msg; // Create can message

				tx_msg.id = 0x7ff; // Set id to 0x7ff
				tx_msg.length = 4;
				tx_msg.data[0] = joystick.position[0];
				tx_msg.data[1] = joystick.position[1];
				tx_msg.data[2] = button;
				tx_msg.data[3] = 1; // Set data[3] to 1 used for signaling that game is over

				can_message_psend(&tx_msg); // Send can message
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
		if (button == 0) { // This is selfmade oled art, that writes HELG with hashtags
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
	usart_init(); // Initialize USART
	can_init(); // Initialize CAN
	sram_init(); // Initialize SRAM
	oled_init(); // Initialize OLED
	adc_init(); // Initialize ADC

	while (1){
		menu(joystick.direction); // Run menu function
		adc_start_conversion(); // Start ADC conversion every time the last is done
    }
}




	