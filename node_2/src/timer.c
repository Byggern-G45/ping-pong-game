#define _IMPORT
#include "sam.h"
#include "sam3x8e.h"
#include "../include/timer.h"

void timer_init(void){
	PMC->PMC_PCER0 |= PMC_PCER0_PID27; //Enable clock for TC0


	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVE| //Waveform mode
                                 TC_CMR_WAVSEL_UP_RC| //UP mode with automatic trigger on RC Compare
                                 TC_CMR_ACPA_CLEAR| //Set TIOA to 0 when RC Compare
                                 TC_CMR_ACPC_SET; //Set TIOA to 1 when RC Compare

	TC0->TC_CHANNEL[0].TC_RC = 840000; //Set RC Compare to 840000, ca 60Hz

	TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN|//Start timer software trigger
								 TC_CCR_SWTRG; //Enable clock
                               

	TC0->TC_CHANNEL[0].TC_IER |= TC_IER_CPCS; //Enable interrupt on RC Compare
	NVIC_EnableIRQ(TC0_IRQn); //Enable interrupt in NVIC

}