#include <sam.h>
//#include "uart.h"
//#include "timer.h"
//#include <utim>


int main(void)
{
	//configure_uart();

	/* Initialize the SAM system */
	SystemInit();
	PIOA->PIO_OER = 1<<20;

	PIOA->PIO_OER = 1<<19;

	PIOA->PIO_PER = 1<<0;
	PIOA->PIO_PER = 1<<1;
	
	//PIOA->PIO_SODR = 1<<19;
	
	PIOA->PIO_CODR = 0xffffffff;

	while (1)
	{
		PIOA->PIO_SODR = 1<<20;
		//delay_ms(1000);
		//PIOA->PIO_CODR = 0x1u<<20;
		//delay_ms(1000);
	}

}
