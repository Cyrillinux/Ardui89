/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#ifndef _89_WIRING_H
#define _89_WIRING_H
// Pins values LSB->MSB
extern unsigned char PROGMEM _pinsTab_PGM[];
// Tableau des adresses des registres SFR pour chaque pin
extern unsigned char PROGMEM digital_pin_to_port_PGM[];
// Fonction pour définir le mode du pin
void pinMode(unsigned char pin, unsigned char state);
// Fonction pour écrire une valeur sur le pin
void digitalWrite(unsigned char pin, unsigned char state);
// Fonction pour lire l'état d'un bit
unsigned char digitalRead(unsigned char pin);
#endif
