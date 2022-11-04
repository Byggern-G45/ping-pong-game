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

#if 0
  #define debugging(a) printf a
#else
  #define debugging(a) (void)0
#endif

#define MCP_FIRST_BYTE 0
#define MCP_BYTE       1
#define MCP_LAST_BYTE  2

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
#define Normal_mode 0b00000000
#define Sleep_mode 0b00100000 //= Set Sleep mode
#define Loopback_mode 0b01000000 //= Set Loopback mode
#define Listen_mode 0b01100000 //= Set Listen-Only mode
#define Configuration_mode 0b10000000 //= Set Configuration mode
#define Mode_address 0x0f //upper data for mode register, next selects bits to be modified
#define Mode_mask 0b11100000 //Mask for mode register
#define Mode_data 0b00000000 //Data for mode register
#define CNF1 0x2a //Address for CNF1 register
#define CNF2 0x29 //Address for CNF2 register
#define CNF3 0x28 //Address for CNF3 register

#define TXB0REG 0b00110001 //TXB0 Extended Identifier Register (EID8:EID0)


/**
 * @brief Initializes and writes testdata to MCP2515
 */
void mcp_init();

/**
 * @brief Resets MCP2515
 */
void mcp_reset();


/**
 * @brief Writes data to register in MCP2515
 * @param address 
 * @param data 
 */
void mcp_write(char address, char data);

/**
 * @brief Reads data from register in MCP2515
 * @param address 
 * @return char 
 */
char mcp_read(char address);

/**
 * @brief Writes data to transmit buffer in MCP2515
 * @param address 
 * @param data 
 */
void mcp_rts(char buffer);

/**
 * @brief Modify bits in register in MCP2515
 * @param address 
 * @param mask 
 * @param data 
 */
void mcp_bit_modify(char address, char mask, char data);

/**
 * @brief Reads status from MCP2515
 * @return char 
 */
char mcp_read_status();

/**
 * @brief Reads RX status from MCP2515
 */
char mcp_read_rx_status();

/**
 * @brief Reads RX buffer from MCP2515
 * @param buffer 
 * @param startpoint 
 * @return char 
 */
char mcp_read_rx_buffer(char buffer, char startpoint, uint8_t state);

/**
 * @brief Writes data to transmit buffer in MCP2515
 * @param buffer 
 * @param startpoint 
 * @param data 
 */
void mcp_load_tx_buffer(char buffer, char startpoint, char data, uint8_t state);

/**
 * @brief Reads TX buffer from MCP2515
 * @param buffer 
 * @param startpoint 
 */
void mcp_read_tx_buffer(char buffer, char startpoint);

/**
 * @brief Sets normal mode in MCP2515 
 */

void mcp_normal_mode();

/**
 * @brief Sets sleep mode in MCP2515 
 */

void mcp_sleep_mode();

/**
 * @brief Sets loopback mode in MCP2515 
 */

void mcp_loopback_mode();

/**
 * @brief Sets listen mode in MCP2515 
 */

void mcp_listen_mode();







#undef ATMEGA162_MCP2515_IMPORT
#undef EXTERN
#endif