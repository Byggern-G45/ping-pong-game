/*
 * GccApplication14.c
 *
 * Created: 3/24/2021 10:30:20 AM
 * Author : kelti
 */ 

#include <avr/io.h>


int main(void)
{
   volatile int8_t int8var = -200; // overflow - warning
   volatile uint8_t uint8var = 100;
   volatile int16_t int16var = -5000;;
   volatile uint16_t uint16var = 2000;;
   volatile int32_t int32var = 2000*5000; // overflow in expression- warning
   int32var = 2000/5000*200;
   int16var = int8var * uint8var;
   int8var++;
   uint16var++;
   int16var++;
   int32var++;
    while (1) 
    {
    }
}

