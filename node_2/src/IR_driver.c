#include "../include/IR_driver.h"

void ADC_init(){
    PMC -> PMC_PCER1 |= PMC_PCER1_PID37; //Enable clock for ADC 
	ADC -> ADC_MR |= ADC_MR_FREERUN_ON; //Enable freerun so adc does not have to wait for trigger
    ADC -> ADC_CHER |= ADC_CHER_CH0; //Enable channel 0
	ADC -> ADC_CR |= ADC_CR_START;
	
}

uint16_t get_IR_value(){
	return ADC_CDR[0];
}

