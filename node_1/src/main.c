#include "../include/atmega162_usart.h"
#include "../include/atmega162_sram.h"
#include "../include/atmega162_adc.h"
#include "../include/atmega162_oled.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf


#define RESET 0b11000000 //Resets internal registers to default state, set Configuration mode.
#define READ 0b00000011 //Read data from register beginning at selected address.
#define READ_RX_BUFFER 0b1001 //0nm0 //When reading a receive buffer, reduces the overhead of a normal Read command by placing the Address Pointer at one of four locations, as indicated by ‘n,m’. Note: The associated RX flag bit (CANINTF.RXnIF) will be cleared after bringing CS high.
#define WRITE 0b00000010 //Write data to register beginning at selected address.
#define LOAD_TX_BUFFER 0b0100 //0abc //When loading a transmit buffer, reduces the overhead of a normal Write command by placing the Address Pointer at one of six locations as indicated by ‘a,b,c’.
#define RTS 0b1000 //0nnn //Instructs controller to begin message transmission sequence for any of the transmit buffers.
#define READ_STATUS 0b10100000 //Quick polling command that reads several status bits for transmit and receive functions.
#define RX_STATUS 0b10110000 //Quick polling command that indicates filter match and message type (standard, extended and/or remote) of received message.
#define BIT_MODIFY 0b00000101 
#define Normal_Operation_mode 0b000
#define Sleep_mode 0b001 //= Set Sleep mode
#define Loopback_mode 0b01000000 //= Set Loopback mode
#define Listen_mode 0b011 //= Set Listen-Only mode
#define Configuration_mode 0b100 //= Set Configuration mode
#define Mode_address 0x0f //upper data for mode register, next selects bits to be modified
#define Mode_mask 0b11100000 //Mask for mode register


void mcp2515_init();


void SPI_init(){
	/* Set MOSI and SCK output and SS, all others input */
	DDRB |= (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
	PORTB |= (1<<PB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


void SPI_Transmit(char data){
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
}


char SPI_Receive(void){
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}



int main() {	
	fdevopen(atmega162_usart_transmit, atmega162_usart_receive); // Enable printf to JTAG
	atmega162_usart_init();
	// atmega162_sram_init();
	// atmega162_joystick_init();
	printf("\n\r\n\rhello\n\r\n\r");
	printf("SPI_init\n\r");
	SPI_init();
	printf("SPI_INITED\n\r");
	printf("MPC2515_INITED\n\r");
	mcp2515_init();
	printf("MPC2515_DONE\n\r");
	
	
	// while (1) {
	// 	atmega162_joystick_start_conversion();
    // }
}

void mcp2515_init() {
	char address = 0x10;
	char data = 0xee;
	char byte;
	PORTB &= ~(1<<PD4);
	SPI_Transmit(RESET);
	PORTB |= (1<<PD4);
	printf("Reset sent\n\r");


	printf("Set Mode \n\r");
	PORTB &= ~(1<<PD4);
	SPI_Transmit(BIT_MODIFY);
	SPI_Transmit(Mode_address);
	SPI_Transmit(Mode_mask);
	SPI_Transmit(Loopback_mode);
	PORTB |= (1<<PD4);
	printf("Loopback Set \n\r");
	
	
	PORTB &= ~(1<<PD4);
	SPI_Transmit(READ);
	SPI_Transmit(Mode_address);
	byte = SPI_Receive();
	PORTB |= (1<<PD4);
	printf("CANCTRL: %x \n\r", byte);
	
	while(1){
	PORTB &= ~(1<<PD4);
	SPI_Transmit(READ);
	SPI_Transmit(0x0e);
	byte = SPI_Receive();
	PORTB |= (1<<PD4);
	printf("CANSTAT: %x \n\r", byte);
	}
	
	

	PORTB = (0<<PD4);
	SPI_Transmit(WRITE);
	SPI_Transmit(address);
	SPI_Transmit(data);
	PORTB = (1<<PD4);


	printf("Wrote: %x\n\r", data);
	PORTB = (0<<PD4);
	SPI_Transmit(READ_STATUS);
	byte = SPI_Receive();
	printf("Status: %x \n\r", byte);
	PORTB = (1<<PD4);


	PORTB = (0<<PD4);
	SPI_Transmit(READ);
	SPI_Transmit(address);
	byte = SPI_Receive();
	PORTB = (1<<PD4);
	printf("Recived: %x \n\r", byte);
	

	
	// Set the MCP2515 into configuration mode
	// mcp2515_bit_modify(MCP_CANCTRL, 0xE0, 0x80);
	// // Set the baud rate to 500kbps
	// mcp2515_bit_modify(MCP_CNF1, 0xFF, 0x00);
	// mcp2515_bit_modify(MCP_CNF2, 0xFF, 0x90);
	// mcp2515_bit_modify(MCP_CNF3, 0xFF, 0x02);
	// // Set the MCP2515 into normal mode
	// mcp2515_bit_modify(MCP_CANCTRL, 0xE0, 0x00);
}