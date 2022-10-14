/**
 * Library for using external MCP2515 on ATmega162. Has function for initialization.
 */

#ifndef ATMEGA162_MCP2515_H
#define ATMEGA162_MCP2515_H




#include "../include/atmega162_spi.h"
#include <avr/io.h>
#include <stdio.h>	// Needed for printf

#ifdef ATMEGA162_MCP2515_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

#if 1
  #define debugging(a) printf a
#else
  #define debugging(a) (void)0
#endif


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


void mcp_init();

void mcp_reset();

void mcp_write(char address, char data);

char mcp_read(char address);

void mcp_rts(char buffer);

void mcp_bit_modify(char address, char mask, char data);

char mcp_read_status();

void mcp_rx_status();

char mcp_read_rx_buffer(char buffer, char startpoint);

void mcp_load_tx_buffer(char buffer, char startpoint, char data);

void mcp_read_tx_buffer(char buffer, char startpoint);






#undef ATMEGA162_MCP2515_IMPORT
#undef EXTERN
#endif