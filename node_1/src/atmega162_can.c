/* atmega162_can.c -- See atmega162_can.h for info */

#define ATMEGA162_CAN_IMPORT
#include "../include/atmega162_can.h"
#include "../include/atmega162_mcp2515.h"

void can_init() {}

void can_message_send(can_message_t* msg) {
    for (uint8_t i = 0; i < msg->length; i++) {
        //printf("%c", msg->data[i]);
    }
}

can_message_t can_message_receive() {}

void can_int_vect() {}
