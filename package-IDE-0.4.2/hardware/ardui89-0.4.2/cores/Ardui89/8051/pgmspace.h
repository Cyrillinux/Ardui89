/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2025-2026
 */
#if defined(ARDUINO_ARCH_8051)
#ifndef _89_PGMSPACE_H
#define _89_PGMSPACE_H
#include <Arduino.h>

#define randomSeed srand

#define pgm_read_byte_near(addr) (*(unsigned char *)(addr))
#define pgm_read_byte(addr) (*(unsigned char *)(addr))

void memcpy_P(unsigned char *dest, const unsigned char __code *src, unsigned int len);
#endif
#else
#warning Not 8051 Architecture !
#endif
