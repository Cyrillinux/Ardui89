/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2025
 */
#if defined(ARDUINO_ARCH_8051)
#ifndef _89_XTOY_H
#define _89_XTOY_H
#include <Arduino.h>
#include <stdlib.h>
#define randomSeed srand

// int_to_string
void int_to_string(int num, char *str);

#endif
#else
#warning Not 8051 Architecture !
#endif
