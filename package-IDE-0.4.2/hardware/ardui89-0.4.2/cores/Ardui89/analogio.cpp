/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024-2026
 * Last revision : 2026/05/14 0.4.2
 */
#include <pins_arduino.h>
#ifdef _89C53_
// ============================================================
// --- ADC ---
// STC15W408AS - ADC_CONTR bit map:
//   Bit 7 : ADC_POWER  (1 = allumé)
//   Bit 6 : SPEED1
//   Bit 5 : SPEED0
//   Bit 4 : ADC_FLAG   (1 = conversion terminée, à effacer par soft)
//   Bit 3 : ADC_START  (écrire 1 pour lancer)
//   Bit 2 : CHS2
//   Bit 1 : CHS1
//   Bit 0 : CHS0
// ============================================================

unsigned int analogRead(unsigned char channel) {
   
    channel-=A0; //Get channel from "pin" (channel)

    // 1. Sélection du canal + power ON
    ADC_CONTR = 0x80 | (channel & 0x07);

    // 2. Temps de charge du condensateur S&H (~20 µs à 29 MHz)
    for (unsigned int i = 0; i < 600; i++) { __asm nop __endasm; }

    // 3. Lancement de la conversion (bit 3 = ADC_START)
    ADC_CONTR |= 0x08;

    // 4. Attente fin de conversion (bit 4 = ADC_FLAG) avec timeout de sécurité
    unsigned int timeout = 10000;
    while (!(ADC_CONTR & 0x10) && --timeout);

    if (timeout == 0) return 9999; // Code erreur

    // 5. Effacement du flag ADC_FLAG
    ADC_CONTR &= ~0x10;

    // 6. Reconstruction du résultat 10 bits
    // ADCCFG = 0x0F → justification GAUCHE :
    //   ADC_RES  = D9 D8 D7 D6 D5 D4 D3 D2  (8 MSBs)
    //   ADC_RESL = D1 D0  0  0  0  0  0  0  (2 LSBs dans bits 7:6)
    return ((unsigned int)ADC_RES << 2) | (ADC_RESL >> 6);
}

void analogPin(unsigned char pin) {// Activer l'entrée analogique
        // 1. Accès aux registres étendus (XFR)
        P_SW2 |= 0x80;
        
        // 2. Pin P1.ch en mode analogique haute impédance
        // channel = pin-A0
        P1ASF |= (1 << pin-A0);   // Active la fonction analogique sur la broche
        P1M1  |= (1 << pin-A0);   // Mode haute impédance (bit M1=1)
        P1M0  &= ~(1 << pin-A0);  // Mode haute impédance (bit M0=0)
        
        // 3. Horloge ADC au minimum (diviseur 32, justification gauche)
        ADCCFG = 0x0F;
        
        // 4. Allumage de l'ADC + sélection du canal
        ADC_CONTR = 0x80 | ((pin-A0) & 0x07);
        
        // 5. Pause de stabilisation
        for (unsigned int i = 0; i < 5000; i++) { __asm nop __endasm; }
}

#endif
