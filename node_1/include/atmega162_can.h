/**
 * Library for using external CAN on ATmega162. Has function for initialization.
 */

#ifndef ATMEGA162_CAN_H
#define ATMEGA162_CAN_H

#include <avr/io.h>

#ifdef ATMEGA162_CAN_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

typedef struct {
    uint16_t id;
    char length;
    char data[8];
} can_message_t;

/**
 * @brief Initialize CAN
 */
void can_init();

/**
 * @brief Send CAN message
 * @param msg CAN message to send
 */
void can_message_send(can_message_t* msg);

/**
 * @brief Receive CAN message
 * @return can_message_t received CAN message
 */
can_message_t can_message_receive();

/**
 * @brief Check if CAN message is received
 */
void can_int_vect();

#undef ATMEGA162_CAN_IMPORT
#undef EXTERN
#endif