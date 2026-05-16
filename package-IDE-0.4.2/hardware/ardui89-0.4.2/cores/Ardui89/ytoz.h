/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2025-2026
 */
#if defined(ARDUINO_ARCH_8051)
#ifndef _89_YTOZ_H
#define _89_YTOZ_H
#include <Arduino.h>
#include <stdlib.h>
#define randomSeed srand

// int_to_string
void int_to_string(int num, char *str);

#endif //_89_YTOZ_H
#else
#warning Not 8051 Architecture !
#endif
