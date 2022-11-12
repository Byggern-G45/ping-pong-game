#define _IMPORT
#include "sam.h"
#include "sam3x8e.h"
#include "../include/timer.h"

void timer_init(void){
	PMC->PMC_PCER0 |= 1<<27; //Enable clock for TC0


	// PIOB->PIO_PDR |=PIO_PDR_P0;//set PB25(PWM2) as output
	// PIOB->PIO_ABSR |=PIO_ABSR_P0;//Peripheral select B

	TC0->TC_CHANNEL[1].TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK1|//Timer clock 1 = MCK/2
                                 TC_CMR_WAVE| //Waveform mode
                                 TC_CMR_WAVSEL_UP_RC| //UP mode with automatic trigger on RC Compare
                                 TC_CMR_ACPA_CLEAR| //Set TIOA to 0 when RC Compare
                                 TC_CMR_ACPC_SET; //Set TIOA to 1 when RC Compare

	TC0->TC_CHANNEL[1].TC_RC = 840000; //Set RC Compare to 840000, ca 60Hz

	TC0->TC_CHANNEL[1].TC_CCR |= TC_CCR_SWTRG| //Start timer software trigger
                                 TC_CCR_CLKEN; //Enable clock

	TC0->TC_CHANNEL[1].TC_IER |= TC_IER_CPCS; //Enable interrupt on RC Compare
	NVIC_EnableIRQ(TC1_IRQn); //Enable interrupt in NVIC
}