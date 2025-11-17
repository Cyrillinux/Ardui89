/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
/* R0 0.3.5 */
#include <delay.h>

// Fonction de délai
void delay(unsigned int ms) {
    unsigned int i, j, adj;
    unsigned long repeat=F_CPU / 1105920;
    for (adj = _STC89_ADJUST_DELAY_ ; adj > 0 ; adj--) {
        for (i = 0; i < ms; i++) {
            for (j = 0; j < 123; j++) {
            // NOP pour un délai de 1 ms approximatif avec une horloge de 12 MHz
            }
        }
    }
}
// Fonction de délai
void delayMicroseconds(unsigned long us) {
    unsigned int i, adj;
    unsigned long repeat=(us * F_CPU) / 12000000;
    for (adj = _STC89_ADJUST_DELAY_ ; adj > 0 ; adj--) {
        for (i = 0; i < repeat; i++) {
            __asm__("nop");
        }
    }
}
