#define PWM_IMPORT
#include "sam.h"
#include "sam3x8e.h"
#include "../include/pwm.h"



void pwm_init(){
	PMC -> PMC_PCER1 |= PMC_PCER1_PID36; //Enable clock for PWM
	PMC -> PMC_PCER0 |= PMC_PCER0_PID13; //Enable clock

	//Assign PWM pins
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	PIOC->PIO_PDR |= PIO_PDR_P19; //Disable PIO control of PWM pin
	
	REG_PWM_CLK |= 1 << 1; // enable clock for PWM
	REG_PWM_CMR5 |= 1 << 1 | 1 << 3; //Master clock / 1024
	REG_PWM_CPRD5 |= 1641; //20ms PWM period
	REG_PWM_CDTY5 |= 1518; //1.5ms PWM duty cycle
	REG_PWM_ENA |= PWM_ENA_CHID5; //enable PWM channel 3
}


//1477 = 2ms
//1518 = 1.5ms
//1559 = 1ms

//This function sets the right duty cycle from a 0-255 input
void convert_to_pwm(uint8_t input){
	uint8_t diff = 0;
	uint16_t duty_cycle = 0;
	diff = (input * 82) / 255;
	duty_cycle = 1559 - diff;
	REG_PWM_CDTY5 = duty_cycle;
}

void solenoid_init(){
	PIOC->PIO_PER |= PIO_PER_P13; //Enable PIO control of solenoid pin
	PIOC->PIO_OER |= PIO_OER_P13; //Set solenoid pin as output
	PIOC->PIO_CODR |= PIO_SODR_P13; //Set solenoid pin low
}

uint8_t solenoid_activated = 0;
void solenoid(uint8_t input){
	if(input == 1){
		PIOC->PIO_SODR |= PIO_CODR_P13; //Set solenoid pin low
		solenoid_activated = 0;
	}
	else if (input == 0 && solenoid_activated == 0){
		PIOC->PIO_CODR |= PIO_SODR_P13; //Set solenoid pin high
		solenoid_activated = 1;
	}
	
}