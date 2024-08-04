/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#if defined(ARDUINO_ARCH_8051)
#ifndef _89_RANDOM_H
#define _89_RANDOM_H
#include <Arduino.h>
#include <stdlib.h>
#define randomSeed srand
unsigned int random(unsigned int mini, ...);
#endif
#else
#warning Not 8051 Architecture !
#endif
