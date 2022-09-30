/* atmega162_sram.c -- See atmega162_sram.h for info */

#define ATMEGA162_SRAM_IMPORT
#include "../include/atmega162_sram.h"

void sram_init() {
	SFIOR = (1<<XMM2) | (0<<XMM1) | (0<<XMM0); 	// Mask out JTAG
	MCUCR = (1<<SRE); 							// Configure ports as bus for external address space
}