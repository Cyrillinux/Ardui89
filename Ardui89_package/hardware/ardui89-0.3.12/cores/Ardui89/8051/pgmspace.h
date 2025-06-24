/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2025
 */
#if defined(ARDUINO_ARCH_8051)
#ifndef _89_PGMSPACE_H
#define _89_PGMSPACE_H
#include <Arduino.h>
#define randomSeed srand
void memcpy_P(unsigned char *dest, const unsigned char __code *src, unsigned int len);
#endif
#else
#warning Not 8051 Architecture !
#endif
