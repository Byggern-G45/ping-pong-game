#define PWM_IMPORT

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
