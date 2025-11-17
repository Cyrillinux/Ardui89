/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 * STC15W408AS-DIP16
 * Last revision : 2024/11/23 : 0.3.7
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <8052.h>
#ifndef _89C53_
#define _89C53_
#endif

#ifndef _STC89_ADJUST_DELAY_
#define _STC89_ADJUST_DELAY_ 8
#endif

//spécial STC15xx Register

#define P_SW2   (*(unsigned char volatile __xdata *)0xFE01) // Registre pour déverrouiller l'accès aux fonctions spéciales
#define RSTCFG  (*(unsigned char volatile __xdata *)0xFF00) // Registre pour configurer la fonction RESET

// Définir les registres de mode pour tous les ports concernés
__sfr __at (0x93) P0M1; // Mode 1 pour le Port 0
__sfr __at (0x94) P0M0; // Mode 0 pour le Port 0
__sfr __at (0x91) P1M1; // Mode 1 pour le Port 1
__sfr __at (0x92) P1M0; // Mode 0 pour le Port 1
__sfr __at (0x95) P2M1; // Mode 1 pour le Port 2
__sfr __at (0x96) P2M0; // Mode 0 pour le Port 2
__sfr __at (0xB1) P3M1; // Mode 1 pour le Port 3
__sfr __at (0xB2) P3M0; // Mode 0 pour le Port 3
__sfr __at (0xB9) P4M1; // Mode 1 pour le Port 4
__sfr __at (0xBA) P4M0; // Mode 0 pour le Port 4
__sfr __at (0xC9) P5M1; // Mode 1 pour le Port 5
__sfr __at (0xCA) P5M0; // Mode 0 pour le Port 5

__sfr __at (0xC0) P4;
__sfr __at (0xC8) P5;

/*  P4  */
__sbit __at (0xC0) P4_0;
__sbit __at (0xC1) P4_1;
__sbit __at (0xC2) P4_2;
__sbit __at (0xC3) P4_3;
__sbit __at (0xC4) P4_4;
__sbit __at (0xC5) P4_5;
__sbit __at (0xC6) P4_6;
__sbit __at (0xC7) P4_7;

/*  P5  */
__sbit __at (0xC9) P5_0;
__sbit __at (0xCA) P5_1;
__sbit __at (0xCB) P5_2;
__sbit __at (0xCC) P5_3;
__sbit __at (0xCD) P5_4;
__sbit __at (0xCE) P5_5;


__sfr __at (0x8E) AUXR;
__sfr __at (0x8E) AUXR2;
__sfr __at (0x97) CLK_DIV;
__sfr __at (0xA2) AUXR1;
__sfr __at (0xD6) T2H;
__sfr __at (0xD7) T2L;

#define P_SW1 AUXR1
#define S1_S0 0x40 //P_SW1.6 / AUXR1_1.6
#define S1_S1 0x80 //P_SW1.7 / AUXR1_1.7

#define LOW  0x0
#define HIGH 0x1

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2


#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial


#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           8

/*
 # Arduino <=> STC15W408AS-DIP16
 (Ardui89 MINI R0)

 D : Arduino digital pins
 A : Arduino analog pins
 LED_BULTIN : D7 (P3.7)
 SDA : A4 (D12/P1.4)
 SCL : A5 (D13/P1.5)

 D   A                                                                 A D
                   +-----------------\_/----------------+
 10 A2 P1.2 -------| 1 P1.2                     P1.1 16 |------- P1.1 A1 9
 11 A3 P1.3 -------| 2 P1.3 (MOSI)              P1.0 15 |------- P1.0 A0 8
 12 A4 P1.4 -------| 3 P1.4 (MISO) (/INT3-TxD2) P3.7 14 |------- P3.7    7
 13 A5 P1.5 -------| 4 P1.5 (SLK)  (/INT2-RxD2) P3.6 13 |------- P3.6    6
  4    P5.4 -------| 5 P5.4              (INT1) P3.3 12 |------- P3.3    3
        Vcc -------| 6 Vcc               (INT0) P3.2 11 |------- P3.2    2
  5    P5.5 -------| 7 P5.5               (TxD) P3.1 10 |------- P3.1    1
        Gnd -------| 8 Gnd                (RxD) P3.0  9 |------- P3.0    0
                   +------------------------------------+
*/

#define MOSI 11
#define MISO 12
#define SCK  13

// i2c wire, direct 8051 pin port remoted
#define SDA 12
#define SCL 13

#define LED_BUILTIN 7

#define A0 8
#define A1 9
#define A2 10
#define A3 11
#define A4 12
#define A5 13

// Définition des adresses des registres SFR
#define _89_P0 0x80
#define _89_P1 0x90
#define _89_P2 0xA0
#define _89_P3 0xB0
#define _89_P4 0xC0
#define _89_P5 0xC8

// Pins values LSB->MSB
#define PINSTABLEVALUE {\
1, 2, 4, 8, 16, 32, 64, 128,\
1, 2, 4, 8, 16, 32\
}

#define PINSPORTAFFECTED {\
/*  0 */ _89_P3 , _89_P3, _89_P3, _89_P3, _89_P5, _89_P5, _89_P3, _89_P3  /*  7 */,\
/*  8 */ _89_P1 , _89_P1, _89_P1, _89_P1, _89_P1, _89_P1 /* 13 */\
}

// Equivalent AVR memory prog affectation
#define PROGMEM __code

#endif

