#include "sam.h"
#include "uart.h"
#include "timer.h"


int main(void)
{
	configure_uart();

	/* Initialize the SAM system */
	SystemInit();
	PIOA->PIO_OER = 0x1u <<20;

	PIOA->PIO_OER = 0x1u <<19;

	PIOA->PIO_PER = 0x1u<<0;
	PIOA->PIO_PER = 0x1u<<1;
	PIOA->PIO_SODR = 0x1u<<19;

	while (1)
	{
		PIOA->PIO_SODR = 0x1u<<20;
		delay_ms(1000);
		PIOA->PIO_CODR = 0x1u<<20;
		delay_ms(1000);
	}

}
