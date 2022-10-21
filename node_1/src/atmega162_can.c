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
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->id >> 3); // ID high
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->id << 5); // ID low
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, 0); // Extended ID high
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, 0); // Extended ID low
    mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->length);  // DLC
    for (uint8_t i = 0; i < msg->length; i++) {
        mcp_load_tx_buffer(TX_BUFFER0, TX_BUFFER_FROMBOTTOM, msg->data[i]); // Data
    }
    mcp_rts(RTS_BUFFER0);
}

can_message_t can_message_receive() {
    mcp_read_rx_status();
    can_message_t msg;
    msg.id = mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM) << 3;
    msg.id |= mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM) >> 5;
    msg.length = mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM);
    for (uint8_t i = 0; i < msg.length; i++) {
        msg.data[i] = mcp_read_rx_buffer(RX_BUFFER0, RX_BUFFER_FROMBOTTOM);
    }
    return msg;
}

void can_int_vect() {}
