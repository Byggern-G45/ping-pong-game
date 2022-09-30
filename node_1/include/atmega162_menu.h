/**
 * Library for menu on OLED using ATmega162.
 */

#ifndef ATMEGA162_MENU_H
#define ATMEGA162_MENU_H

#include <avr/io.h>

#ifdef ATMEGA162_MENU_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

void menu101();
void menu102();
void menu103();
void menu201();
void menu202();
void menu203();
void menu301();
void menu302();
void menu303();

#undef ATMEGA162_MENU_IMPORT
#undef EXTERN
#endif