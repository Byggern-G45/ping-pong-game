/* atmega162_mcp2515.c -- See atmega162_mcp2515.h for info */

#define ATMEGA162_MCP2515_IMPORT
#include "../include/atmega162_mcp2515.h"


#define RESET 0b11000000 //Resets internal registers to default state, set Configuration mode.
#define READ 0b00000011 //Read data from register beginning at selected address.
#define READ_RX_BUFFER 0b10010000//0nm0 //When reading a receive buffer, reduces the overhead of a normal Read command by placing the Address Pointer at one of four locations, as indicated by ‘n,m’. Note: The associated RX flag bit (CANINTF.RXnIF) will be cleared after bringing CS high.
#define RX_BUFFER0 0b00000000
#define RX_BUFFER1 0b00000001
#define RX_BUFFER_FROMTOP 0b00000001
#define RX_BUFFER_FROMBOTTOM 0b00000000


#define WRITE 0b00000010 //Write data to register beginning at selected address.
#define LOAD_TX_BUFFER 0b01000000 //0abc //When loading a transmit buffer, reduces the overhead of a normal Write command by placing the Address Pointer at one of six locations as indicated by ‘a,b,c’.
#define TX_BUFFER0 0b00000000
#define TX_BUFFER1 0b00000001
#define TX_BUFFER2 0b00000010
#define TX_BUFFER_FROMTOP 0b00000001
#define TX_BUFFER_FROMBOTTOM 0b00000000

#define RTS 0b10000000 //0nnn //Instructs controller to begin message transmission sequence for any of the transmit buffers.
#define RTS_BUFFER0 0b00000001
#define RTS_BUFFER1 0b00000010
#define RTS_BUFFER2 0b00000100
#define READ_STATUS 0b10100000 //Quick polling command that reads several status bits for transmit and receive functions.
#define RX_STATUS 0b10110000 //Quick polling command that indicates filter match and message type (standard, extended and/or remote) of received message.
#define BIT_MODIFY 0b00000101 
#define Normal_Operation_mode 0b000
#define Sleep_mode 0b001 //= Set Sleep mode
#define Loopback_mode 0b01000000 //= Set Loopback mode
#define Listen_mode 0b011 //= Set Listen-Only mode
#define Configuration_mode 0b100 //= Set Configuration mode
#define Mode_address 0x0e //upper data for mode register, next selects bits to be modified
#define Mode_mask 0b11100000 //Mask for mode register
#define Mode_data 0b00000000 //Data for mode register


void mcp2515_init();


void mcp_reset(){
	PORTB &= ~(1<<PD4);
	SPI_Transmit(RESET);
	PORTB |= (1<<PD4);
	printf("Reset sent\n\r");
}

char mcp_read(char address){
	PORTB &= ~(1<<PD4);
	SPI_Transmit(READ);
	SPI_Transmit(address);
	int byte = SPI_Receive();
	PORTB |= (1<<PD4);
	printf("Recived: %x from %x \n\r", byte, address);
	return byte;
}

void mcp_write(char address, char data){
	PORTB &= ~(1<<PD4);
	SPI_Transmit(WRITE);
	SPI_Transmit(address);
	SPI_Transmit(data);
	PORTB |= (1<<PD4);
	printf("Wrote %x to %x\n\r" ,data, address);
}

void mcp_bit_modify(char address, char mask, char data){
	PORTB &= ~(1<<PD4);
	SPI_Transmit(BIT_MODIFY);
	SPI_Transmit(address);
	SPI_Transmit(mask);
	SPI_Transmit(data);
	PORTB |= (1<<PD4);
	printf("Bit modify sent\n\r");
}

char mcp_read_status(){
	PORTB &= ~(1<<PD4);
	SPI_Transmit(READ_STATUS);
	int byte = SPI_Receive();
	int byte2 = SPI_Receive();
	PORTB |= (1<<PD4);
	printf("Status: %x repeat %x\n\r", byte, byte2);
	return byte;
}

char mcp_read_rx_buffer(char buffer, char startpoint){
	char address = READ_RX_BUFFER;
	address |= (buffer << 2) | (startpoint << 1);
	PORTB &= ~(1<<PD4);
	SPI_Transmit(address);
	int byte = SPI_Receive();
	PORTB |= (1<<PD4);
	printf("RXBUFFER: %x from %x \n\r", byte, address);
	return byte;
}

void mcp_load_tx_buffer(char buffer, char startpoint, char data){
	char address = LOAD_TX_BUFFER;
	address |= (buffer << 2) | (startpoint << 1);
	PORTB &= ~(1<<PD4);
	SPI_Transmit(address);
	SPI_Transmit(data);
	PORTB |= (1<<PD4);
	printf("RXBUFFER: %x from %x \n\r", data, address);
}

void mcp_rts(char buffer){
	char address = RTS;
	address |= (buffer << 1);
	PORTB &= ~(1<<PD4);
	SPI_Transmit(address);
	PORTB |= (1<<PD4);
}
 char mcp_read_rx_status(){
	PORTB &= ~(1<<PD4);
	SPI_Transmit(RX_STATUS);
	int byte = SPI_Receive();
	int byte2 = SPI_Receive();
	PORTB |= (1<<PD4);
	switch (byte & 0b11000000){
		case 00:
		printf("No RX message\n\r");
		break;
		case 01:
		printf("Message in buffer 0\n\r");
		break;
		case 10:
		printf("Message in buffer 1\n\r");
		break;
		case 11:
		printf("Message in both buffers\n\r");
		break;
	}

	switch (byte & 0b00011000){
		case 00:
		printf("Message is standard\n\r");
		break;
		case 01:
		printf("Message is standard remote\n\r");
		break;
		case 10:
		printf("Message is extended\n\r");
		break;
		case 11:
		printf("Message is extended remote\n\r");
		break;
	}

	switch (byte & 0b00000111){
		case 000:
		printf("RXF0\n\r");
		break;
		case 001:
		printf("RXF1\n\r");
		break;
		case 010:
		printf("RXF2\n\r");
		break;
		case 011:
		printf("RXF3\n\r");
		break;
		case 100:
		printf("RXF4\n\r");
		break;
		case 101:
		printf("RXF5\n\r");
		break;
		case 110:
		printf("RXF0 rollover to RXB0\n\r");
		break;
		case 111:
		printf("RXF1 rollover to RXB1\n\r");
		break;
	}
	return byte;
 }

void mcp2515_init() {
	
	mcp_reset();
	mcp_read_status();
    mcp_bit_modify(Mode_address, Mode_mask, Loopback_mode);
	mcp_read_status();
	
	mcp_read(Mode_address);
	
	mcp_read(0x0f);
	mcp_read(0x0e);
	mcp_read(0x7f);
	mcp_read(0x7e);

	mcp_write(0x10, 0xaa);
	mcp_write(0x20, 0xbb);
	mcp_write(0x30, 0xcc);
	mcp_write(0x40, 0xee);
	mcp_write(0x50, 0xff);

	mcp_read(0x10);
	mcp_read(0x20);
	mcp_read(0x30);
	mcp_read(0x40);
	mcp_read(0x50);

	mcp_read(0x0f);
	mcp_read_status(0x0f);
	mcp_read(0x0e);
	mcp_read_status(0x0e);

	mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, 0x01);
	mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMTOP, 0x02);
	mcp_load_tx_buffer(TX_BUFFER1, TX_BUFFER_FROMBOTTOM, 0x03);
	mcp_load_tx_buffer(TX_BUFFER1, TX_BUFFER_FROMTOP, 0x04);
	mcp_load_tx_buffer(TX_BUFFER2, TX_BUFFER_FROMBOTTOM, 0x05);
	mcp_load_tx_buffer(TX_BUFFER2, TX_BUFFER_FROMTOP, 0x06);
	

	mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM);
	mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMTOP);
	mcp_read_rx_buffer(RX_BUFFER1, RX_BUFFER_FROMBOTTOM);
	mcp_read_rx_buffer(RX_BUFFER1, RX_BUFFER_FROMTOP);

	mcp_rts(RTS_BUFFER0);

	mcp_read_rx_status();


	

	
	// Set the MCP2515 into configuration mode
	// mcp2515_bit_modify(MCP_CANCTRL, 0xE0, 0x80);
	// // Set the baud rate to 500kbps
	// mcp2515_bit_modify(MCP_CNF1, 0xFF, 0x00);
	// mcp2515_bit_modify(MCP_CNF2, 0xFF, 0x90);
	// mcp2515_bit_modify(MCP_CNF3, 0xFF, 0x02);
	// // Set the MCP2515 into normal mode
	// mcp2515_bit_modify(MCP_CANCTRL, 0xE0, 0x00);
}