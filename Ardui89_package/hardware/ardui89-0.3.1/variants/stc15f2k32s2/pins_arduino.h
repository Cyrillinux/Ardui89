/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 * STC15F2K16 or 32
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <8052.h>
#ifndef _89C53_
#define _89C53_
#endif

#define _STC89_ADJUST_DELAY_ 8

//spécial STC15xx Register

__sfr __at (0xC0) P4 ;
__sfr __at (0xC8) P5 ;

/*  P4  */
__sbit __at (0xC0) P4_0 ;
__sbit __at (0xC1) P4_1 ;
__sbit __at (0xC2) P4_2 ;
__sbit __at (0xC3) P4_3 ;
__sbit __at (0xC4) P4_4 ;
__sbit __at (0xC5) P4_5 ;
__sbit __at (0xC6) P4_6 ;
__sbit __at (0xC7) P4_7 ;

/*  P5  */
__sbit __at (0xC9) P5_0 ;
__sbit __at (0xCA) P5_1 ;
__sbit __at (0xCB) P5_2 ;
__sbit __at (0xCC) P5_3 ;
__sbit __at (0xCD) P5_4 ;
__sbit __at (0xCE) P5_5 ;

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
 # Arduino <=> STC15F2K16 or 32 pinout equivalent
 (Ardui89 UNO R0)

 D : Arduino digital pins
 A : Arduino analog pins
 LED_BULTIN : D13 (P2.5)
 SDA : A4 (D22/P1.4)
 SCL : A5 (D23/P1.5)

 A   D                                                                         D
                   +---------------------\_/--------------------+
    14 P2.6 -------|  1 P2.6 (CCP1)            (CCP0_3) P2.5 28 |------- P2.5 13
    15 P2.7 -------|  2 P2.7 (CCP2)             (ECI_3) P2.4 27 |------- P2.4 12
 A0 18 P1.0 -------|  3 P1.0 (RxD2)            (MOSI_2) P2.3 26 |------- P2.3 11
 A1 19 P1.1 -------|  4 P1.1 (TxD2)            (MISO_2) P2.2 25 |------- P2.2 10
 A2 20 P1.2 -------|  5 P1.2 (ECI)             (SCLK_2) P2.1 24 |------- P2.1  9
 A3 21 P1.3 -------|  6 P1.3 (MOSI)        (RSTOUT_LOW) P2.0 23 |------- P2.0  8
 A4 22 P1.4 -------|  7 P1.4 (MISO) (INT3/TxD_2/CCP2_2) P3.7 22 |------- P3.7  7
 A5 23 P1.5 -------|  8 P1.5 (SCLK)  (NT2/RxD_2/CCP1_2) P3.6 21 |------- P3.6  6
        XT2 -------|  9 P1.6 (XTAL2) (T1/T0CLKO/CCP0_2) P3.5 20 |------- P3.5  5
        XT1 -------| 10 P1.7 (XTAL1)  (T0/T1CLKO/ECI_2) P3.4 19 |------- P3.4  4
    16  RST -------| 11 P5.4 (MCLKO)             (INT1) P3.3 18 |------- P3.3  3
        Vcc -------| 12 Vcc                      (INT0) P3.2 17 |------- P3.2  2
    17 P5.5 -------| 13 P5.5                   (TxD/T2) P3.1 16 |------- P3.1  1
       Gnd  -------| 14  Gnd          (RxD/INT4/T2CLKO) P3.0 15 |------- P3.0  0
                   +--------------------------------------------+
*/

#define MOSI 21
#define MISO 22
#define SCK  23

// i2c wire, direct 8051 pin port remoted
#define SDA 22
#define SCL 23

#define LED_BUILTIN 13

#define A0 18
#define A1 19
#define A2 20
#define A3 21
#define A4 22
#define A5 23

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
1, 2, 4, 8, 16, 32, 64, 128,\
16, 32, 1, 2, 4, 8, 16, 32\
}

#define PINSPORTAFFECTED {\
/*  0 */ _89_P3 , _89_P3, _89_P3, _89_P3, _89_P3, _89_P3, _89_P3, _89_P3  /*  7 */,\
/*  8 */ _89_P2 , _89_P2, _89_P2, _89_P2, _89_P2, _89_P2, _89_P2, _89_P2  /* 15 */,\
/* 16 */ _89_P5 , _89_P5, _89_P1, _89_P1, _89_P1, _89_P1, _89_P1, _89_P1  /* 23 */\
}

// Equivalent AVR memory prog affectation
#define PROGMEM __code

#endif
