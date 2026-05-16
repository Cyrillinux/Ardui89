/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <8052.h>

#ifndef _STC89_ADJUST_TONE_
#define _STC89_ADJUST_TONE_ 200/3000
#endif

#define LOW  0x0
#define HIGH 0x1

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2


#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial


#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           8

// 8051/89C5x
/*    Arduino 8051 pinout
 D                                                                D  A
               +-------------------------------+
 8 P1.0 -------|  1  P1.0              VCC  40 |------ VCC
 9 P1.1 -------|  2  P1.1             P0.0  39 |------ P0.0 (AD0) 31 A7
 2 P1.2 -------|  3  P1.2             P0.1  38 |------ P0.1 (AD1) 30 A6
 3 P1.3 -------|  4  P1.3             P0.2  37 |------ P0.2 (AD2) 29 A5 SCL
 4 P1.4 -------|  5  P1.4             P0.3  36 |------ P0.3 (AD3) 28 A4 SDA
 5 P1.5 (MOSI)-|  6  P1.5 (MOSI)      P0.4  35 |------ P0.4 (AD4) 27 A3
 6 P1.6 (MISO)-|  7  P1.6 (MISO)      P0.5  34 |------ P0.5 (AD5) 26 A2
 7 P1.7 (SCK)--|  8  P1.7 (SCK)       P0.6  33 |------ P0.6 (AD6) 25 A1
    RST -------|  9  RST              P0.7  32 |------ P0.7 (AD7) 24 A0
 0 P3.0 -------| 10  P3.0 (RXD)   (VPP) EA  31 |------ EA   (VPP)
 1 P3.1 -------| 11  P3.1 (TXD)  (PRG) ALE  30 |------ ALE  (PRG)
10 P3.2 -------| 12  P3.2 (INT0)     /PSEN  29 |------ /PSEN
11 P3.3 -------| 13  P3.3 (INT1)      P2.7  28 |------ P2.7 (A15) 23
12 P3.4 -------| 14  P3.4 (T0)        P2.6  27 |------ P2.6 (A14) 22
13 P3.5 -------| 15  P3.5 (T1)        P2.5  26 |------ P2.5 (A13) 21
14 P3.6 -------| 16  P3.6 (WR)        P2.4  25 |------ P2.4 (A12) 20
15 P3.7 -------| 17  P3.7 (RD)        P2.3  24 |------ P2.3 (A11) 19
  XTAL2 -------| 18  XTAL2            P2.2  23 |------ P2.2 (A10) 18
  XTAL1 -------| 19  XTAL1 P          P2.1  22 |------ P2.1 (A9)  17
    GND -------| 20  GND              P2.0  21 |------ P2.0 (A8)  16
               +-------------------------------+
*/

#define MOSI 5
#define MISO 6
#define SCK  7

// i2c wire, direct 8051 pin port remoted
#define SDA 28
#define SCL 29

#define LED_BUILTIN 13

#define A0 24
#define A1 25
#define A2 26
#define A3 27
#define A4 28
#define A5 29
#define A6 30
#define A7 31

// Définition des adresses des registres SFR
#define _89_P0 0x80
#define _89_P1 0x90
#define _89_P2 0xA0
#define _89_P3 0xB0

// Pins values LSB->MSB
#define PINSTABLEVALUE {\
1, 2, 4, 8, 16, 32, 64, 128,\
1, 2, 4, 8, 16, 32, 64, 128,\
1, 2, 4, 8, 16, 32, 64, 128,\
128, 64, 32, 16, 8, 4, 2, 1\
}

#define PINSPORTAFFECTED {\
/*  0 */ _89_P3 , _89_P3, _89_P1, _89_P1, _89_P1, _89_P1, _89_P1, _89_P1  /*  7 */,\
/*  8 */ _89_P1 , _89_P1, _89_P3, _89_P3, _89_P3, _89_P3, _89_P3, _89_P3  /* 15 */,\
/* 16 */ _89_P2 , _89_P2, _89_P2, _89_P2, _89_P2, _89_P2, _89_P2, _89_P2  /* 23 */,\
/* 24 */ _89_P0 , _89_P0, _89_P0, _89_P0, _89_P0, _89_P0, _89_P0, _89_P0  /* 31 */\
}

// Equivalent AVR memory prog affectation
#define PROGMEM __code

#endif
