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