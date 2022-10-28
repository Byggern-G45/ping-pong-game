/* atmega162_can.c -- See atmega162_can.h for info */

#define ATMEGA162_CAN_IMPORT
#include "../include/atmega162_can.h"
#include "../include/atmega162_mcp2515.h"

void can_init() {
    SPI_init();
    mcp_init();
}

void can_message_send(can_message_t* msg) {
    if (msg->length > 0b1111) {
        msg->length = 0b1111;
    }
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->id >> 3, MCP_FIRST_BYTE); // ID high
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->id << 5, MCP_BYTE); // ID low
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, 0, MCP_BYTE); // Extended ID high
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, 0, MCP_BYTE); // Extended ID low
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->length, MCP_BYTE);  // DLC
    for (uint8_t i = 0; i < msg->length; i++) {
        mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->data[i], i == msg->length - 1 ? MCP_LAST_BYTE : MCP_BYTE); // Data
    }
    //mcp_rts(RTS_BUFFER0); // Uncomment this after
}

/*
void can_message_send(can_message_t* msg) {
    if (msg->length > 0b1111) {
        msg->length = 0b1111;
    }
    mcp_write(0b00110000 + 1, msg->id >> 3); // ID high
    mcp_write(0b00110000 + 2, msg->id << 5); // ID low
    mcp_write(0b00110000 + 3, 0); // Extended ID high
    mcp_write(0b00110000 + 4, 0); // Extended ID low
    mcp_write(0b00110000 + 5, msg->length);  // DLC
    for (uint8_t i = 0; i < msg->length; i++) {
        mcp_write(0b00110000 + 6 + i, msg->data[i]); // Data
    }
    mcp_rts(RTS_BUFFER0);
    mcp_write(asdhgasd, 0)
}
*/

/*
can_message_t can_message_receive() {
    mcp_read_rx_status();
    can_message_t msg;
	
    msg.id = mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM, MCP_FIRST_BYTE) << 3;
    msg.id |= mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM, MCP_BYTE) >> 5;
	mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM, MCP_BYTE); // Extended ID high
    mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM, MCP_BYTE); // Extended ID low
    msg.length = mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM, MCP_BYTE);

    printf("msg.id: %d\n", msg.id);
	printf("msg.length: %d\n", msg.length);

    for (uint8_t i = 0; i < msg.length; i++) {
        msg.data[i] = mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM, i == msg.length - 1 ? MCP_LAST_BYTE : MCP_BYTE);
        printf("msg.data[%d] = %d\n", i, msg.data[i]);
    }
    return msg;
}
*/

can_message_t can_message_receive() {
    //mcp_read_rx_status();
    can_message_t msg;
	
    msg.id = mcp_read(0b00110000 + 1) << 3;
    msg.id |= mcp_read(0b00110000 + 2) >> 5;
	mcp_read(0b00110000 + 3); // Extended ID high
    mcp_read(0b00110000 + 4); // Extended ID low
    msg.length = mcp_read(0b00110000 + 5);
    for (uint8_t i = 0; i < msg.length; i++) {
        msg.data[i] = mcp_read(0b00110000 + 6 + i);
    }
    return msg;
}


void can_int_vect() {}
