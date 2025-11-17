/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 * Last revision : 2024/11/23 : 0.3.7
 */
#include <pins_arduino.h>
// Pins values LSB->MSB
unsigned char PROGMEM _pinsTab_PGM[]=PINSTABLEVALUE;

// Tableau des adresses des registres SFR pour chaque pin
const unsigned char PROGMEM digital_pin_to_port_PGM[] = PINSPORTAFFECTED;

// Fonction pour définir le mode du pin
void pinMode(unsigned char pin, unsigned char state) {
    unsigned char bit_mask = _pinsTab_PGM[pin]; // Masque de bit
    if (state==OUTPUT) {
        if (digital_pin_to_port_PGM[pin] == _89_P0) {
            P0 |= bit_mask;  // Met le bit à 1 pour définir le pin comme sortie
#ifdef _89C53_
            P0M1 &= ~bit_mask; // M1 configuration with 0 for this bit
            P0M0 |= bit_mask; // M0 configuration with 0 for this bit
#endif
        } else if (digital_pin_to_port_PGM[pin] == _89_P1) {
            P1 |= bit_mask;
#ifdef _89C53_
            P1M1 &= ~bit_mask; // M1 configuration with 0 for this bit
            P1M0 |= bit_mask; // M0 configuration with 0 for this bit
#endif
        } else if (digital_pin_to_port_PGM[pin] == _89_P2) {
            P2 |= bit_mask;
#ifdef _89C53_
            P2M1 &= ~bit_mask; // M1 configuration with 0 for this bit
            P2M0 |= bit_mask; // M0 configuration with 0 for this bit
#endif
        } else if (digital_pin_to_port_PGM[pin] == _89_P3) {
            P3 |= bit_mask;
#ifdef _89C53_
            P3M1 &= ~bit_mask; // M1 configuration with 0 for this bit
            P3M0 |= bit_mask; // M0 configuration with 0 for this bit
#endif
        }
#ifdef _89C53_
          else if (digital_pin_to_port_PGM[pin] == _89_P4) {
            P4 |= bit_mask;
            P4M1 &= ~bit_mask; // M1 configuration with 0 for this bit
            P4M0 |= bit_mask; // M0 configuration with 0 for this bit
        } else if (digital_pin_to_port_PGM[pin] == _89_P5) {
            P5 |= bit_mask;
            P5M1 &= ~bit_mask; // M1 configuration with 0 for this bit
            P5M0 |= bit_mask; // M0 configuration with 0 for this bit
        }
#endif
    } else {
        if (digital_pin_to_port_PGM[pin] == _89_P0) {
            P0 &= ~bit_mask; // Met le bit à 0 pour définir le pin comme entrée
        } else if (digital_pin_to_port_PGM[pin] == _89_P1) {
            P1 &= ~bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P2) {
            P2 &= ~bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P3) {
            P3 &= ~bit_mask;
        }
#ifdef _89C53_
          else if (digital_pin_to_port_PGM[pin] == _89_P4) {
            P4 &= ~bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P5) {
            P5 &= ~bit_mask;
        }
#endif
    }
    if (state==INPUT_PULLUP) {// Activer la résistance de pull-up si le port le supporte
        if (digital_pin_to_port_PGM[pin] == _89_P1) {
            P1 |= bit_mask;  // Activation de la résistance de pull-up sur P1
        } else if (digital_pin_to_port_PGM[pin] == _89_P2) {
            P2 |= bit_mask;  // Activation de la résistance de pull-up sur P3
        } else if (digital_pin_to_port_PGM[pin] == _89_P3) {
            P3 |= bit_mask;  // Activation de la résistance de pull-up sur P3
        }
#ifdef _89C53_
          else if (digital_pin_to_port_PGM[pin] == _89_P4) {
            P4 |= bit_mask;  // Activation de la résistance de pull-up sur P3
        } else if (digital_pin_to_port_PGM[pin] == _89_P5) {
            P5 |= bit_mask;  // Activation de la résistance de pull-up sur P3
        }
#endif
    }
}

// Fonction pour écrire une valeur sur le pin
void digitalWrite(unsigned char pin, unsigned char state) {
    unsigned char bit_mask = _pinsTab_PGM[pin]; // Masque de bit
    if (state) {
        if (digital_pin_to_port_PGM[pin] == _89_P0) {
            P0 |= bit_mask;  // Met le bit à 1 pour mettre le pin à l'état haut
        } else if (digital_pin_to_port_PGM[pin] == _89_P1) {
            P1 |= bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P2) {
            P2 |= bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P3) {
            P3 |= bit_mask;
        }
#ifdef _89C53_
          else if (digital_pin_to_port_PGM[pin] == _89_P4) {
            P4 |= bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P5) {
            P5 |= bit_mask;
        }
#endif
    } else {
        if (digital_pin_to_port_PGM[pin] == _89_P0) {
            P0 &= ~bit_mask; // Met le bit à 0 pour mettre le pin à l'état bas
        } else if (digital_pin_to_port_PGM[pin] == _89_P1) {
            P1 &= ~bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P2) {
            P2 &= ~bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P3) {
            P3 &= ~bit_mask;
        }
#ifdef _89C53_
          else if (digital_pin_to_port_PGM[pin] == _89_P4) {
            P4 &= ~bit_mask;
        } else if (digital_pin_to_port_PGM[pin] == _89_P5) {
            P5 &= ~bit_mask;
        }
#endif
    }
}
// Fonction pour lire l'état d'un bit
unsigned char digitalRead(unsigned char pin) {
    unsigned char bit_mask = _pinsTab_PGM[pin]; // Masque de bit
    unsigned char port = digital_pin_to_port_PGM[pin];
    unsigned char value = 0x00;
    if (port == _89_P0) {
        value = P0 & bit_mask;
    } else if (port == _89_P1) {
        value = P1 & bit_mask;
    } else if (port == _89_P2) {
        value = P2 & bit_mask;
    } else if (port == _89_P3) {
        value = P3 & bit_mask;
    }
#ifdef _89C53_
      else if (port == _89_P4) {
        value = P4 & bit_mask;
    } else if (port == _89_P5) {
        value = P5 & bit_mask;
    }
#endif
    return value ? 0x01 : 0x00;
}
