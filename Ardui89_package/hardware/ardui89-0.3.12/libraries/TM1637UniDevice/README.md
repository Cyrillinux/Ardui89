TM1637 Universal Arduino AVR 8051 Device
========================================

V.0.0.4
Bugs fixed in AVR using.
Hexademal chars bugs fixed in AVR using.

Universal Arduino library for TM1637 (LED Driver)

Arduino achitectures : AVR, 8051, STC89C51, STC89C52...

See too : https://sourceforge.net/projects/stc89/

Very easy using

just using 3 lines, example :

  TM1637Device display;             // New 7 seg display

  TM1637_init(display, 2, 3);       // Init TM1637 Display : CLK = pin 2 / DIO = pin 3
 
  TM1637_printString("1234");       // Print 1234 on 4 x 7 segments module
  
  or
  
  TM1637_printString("=-7°F");       // Print = - 7°F
  
see all examples in example TM1637Demo, like   TM1637_setBrightness(display, 7), etc...


* DISLAIMER OF ALL WARRANTIES *

# Arduino <=> 8051/89C5x/STC32G12K128 pinout equivalent
(Ardui89 Cinque Uno/Due/128k R0)

D : Arduino digital pins
A : Arduino analog pins
LED_BULTIN : D13 (P3.5)

 D                                                                 D  A
               +---------------\/--------------+
               |                               |
 7 P1.0 -------|  1  P1.0              VCC  40 |------ VCC
 8 P1.1 -------|  2  P1.1             P0.0  39 |------ P0.0 (AD0) 31 A7
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
