/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
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
