/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <Arduino.h>
#include <Main89.h>

// Special setup for any variants > 89C52
#ifdef _89C53_
void _stc89_variant_setup(void) {
    AUXR1 &= 0xFE; // set AUXR1.0 to 0 disable Reset on P5.4
    AUXR2 |= 0x01; // Met AUXR2.0 à 1 pour libérer P1.6 et P1.7 en E/S
    P_SW2 = 0x80; // Activer l'accès aux registres spéciaux
    RSTCFG = 0x00; // Désactiver RESET sur P5.5, la rendant disponible comme GPIO
}
#endif

// Arduino primaries functions
// MAIN
void main(void) {
#ifdef _89C53_
    _stc89_variant_setup();
#endif
    setup();
    while (1) loop();
}
