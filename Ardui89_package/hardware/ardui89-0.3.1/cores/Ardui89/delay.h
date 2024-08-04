/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#ifndef _89_DELAY_H
#define _89_DELAY_H

#include <pins_arduino.h>

#ifndef _STC89_ADJUST_DELAY_
#define _STC89_ADJUST_DELAY_ 1
#endif

void delay(unsigned int ms);
void delayMicroseconds(unsigned long us);
#endif

