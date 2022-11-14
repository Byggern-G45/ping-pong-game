/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "../include/can_interrupt.h"

#include <stdio.h>
#include <sam.h>


#include "../include/printf-stdarg.h"
#include "../include/can_controller.h"
#include "../include/pwm.h"
#include "../include/solenoid.h"
#include "../include/regulator.h"

#define DEBUG_INTERRUPT 0


void can_interrupt_init(void) {
	
}

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			printf("joystick: %d\t", message.data[1]);
			//printf("joystick perc: %d\n", message.data[1]*200/255 - 100);
			pi_regulator_init(&message.data[1]);
			can_receive(&message, 1);
			convert_to_pwm(message.data[0]);
			solenoid(message.data[2]);
			
			//printf("CAN0 interrupt: Mailbox 1 event\n\r");
		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			pi_regulator_init(&message.data[1]);
			can_receive(&message, 2);
			convert_to_pwm(message.data[0]);
			solenoid(message.data[2]); //Hvem av boksene kommer data på?
			
			//printf("CAN0 interrupt: Mailbox 2 event\n\r");
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}

		if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
		if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
		for (int i = 0; i < message.data_length; i++)
		{
			if(DEBUG_INTERRUPT)printf("%d ", message.data[i]);
		}
		if(DEBUG_INTERRUPT)printf("\n\r");
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}
