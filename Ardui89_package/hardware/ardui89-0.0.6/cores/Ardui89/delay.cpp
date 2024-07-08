/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <delay.h>
// Fonction de délai
void delay(unsigned int ms) {
    unsigned int i, j;
    unsigned long repeat=(123 * 11059200) / F_CPU;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++) {
            // NOP pour un délai de 1 ms approximatif avec une horloge de 12 MHz
        }
    }
}
// Fonction de délai
void delayMicroseconds(unsigned int us) {
    unsigned int i;
    for (i = 0; i < us; i++) {
        __asm__("nop");
    }
}
