/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#ifndef _89_TONE_H
#define _89_TONE_H
#include <Arduino.h>
#include <stdarg.h>
// Timer 0 Interruption vector
extern void timer0_isr(void) __interrupt (1);
// Fonction pour activer le signal PWM
void _89_delay_timer(unsigned char th, unsigned char tl);
// Fonction pour générer un délai d'une milliseconde
//void _89_delay_ms(unsigned int ms);
// play tone
void _89_tone_play(unsigned char pin, unsigned int freq, unsigned int duration_ms);
// stop tone
// void _89_tone_stop(unsigned char pin, unsigned char state);
// tone
void tone(unsigned char pin, unsigned int freq, ...);
// Fonction pour désactiver le signal PWM
//void noTone(unsigned char pin, ...);
void noTone(unsigned char pin);
#endif
