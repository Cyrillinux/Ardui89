# Ardui89 C IDE Beta 0.1.0
Under GPL license

Arduino for 8051 family (STC89C51; STC89C52, STC15F2K32S2... )

* DISCLAIMER OF ALL WARRANTIES *

not official package and patch

This project is new projet, just starting !

MacOS only for instant ! But more platforms soon !

This package and this patch for Arduino 1 8 19 allows to COMPIL a .ino for 8051 family in C and UPLOAD into STC89Cxx Family

#Content

* Arduino compatible Package => ardui89   -harware
                                        -tools      -sdcc compiler
                                                    -stcflahisp.py

#Todo
Create all equivalent Arduino basic functions
Install Arduino.h, pins_arduino.h, .... All Arduino compatible files directly in package...

#Installation and test

1/ Donwload Arduino >= V1.8.19 

2/ Launch Arduino

3/ In Arduino->Preferences->Additional Board Manager URLS
    add http://bacciel.com/tools/package_ardui89_index.json
    
4/ In Tools->Boards:...->Board Manager
    search "ardui89"
    select and install "ardui89"
    
5/ In Tools->Board:...
    select "Board : "STC89C51" "STC89C52" "....""
    
6/ Demos :
    Use Blink.ino in basics examples or in Ardui89_demos path :
    Hello.ino
    Howareyou.ino
    
    and build and upload !

Many thanks

Cyril BARBATO

http://bacciel.com
cyril.barbato@gmx.com



# Arduino 8051/89C5x Pinout equivalent

 D                                                                 D  A
               +-------------------------------+
               |                               |
 0 P1.0 -------|  1  P1.0              VCC  40 |------ VCC
 1 P1.1 -------|  2  P1.1             P0.0  39 |------ P0.0 (AD0) 31 A7
 2 P1.2 -------|  3  P1.2             P0.1  38 |------ P0.1 (AD1) 30 A6
 3 P1.3 -------|  4  P1.3             P0.2  37 |------ P0.2 (AD2) 29 A5
 4 P1.4 -------|  5  P1.4             P0.3  36 |------ P0.3 (AD3) 28 A4
 5 P1.5 (MOSI)-|  6  P1.5 (MOSI)      P0.4  35 |------ P0.4 (AD4) 27 A3
 6 P1.6 (MISO)-|  7  P1.6 (MISO)      P0.5  34 |------ P0.5 (AD5) 26 A2
 7 P1.7 (SCK)--|  8  P1.7 (SCK)       P0.6  33 |------ P0.6 (AD6) 25 A1
    RST -------|  9  RST              P0.7  32 |------ P0.7 (AD7) 24 A0
 8 P3.0 -------| 10  P3.0 (RXD)   (VPP) EA  31 |------ EA   (VPP)
 9 P3.1 -------| 11  P3.1 (TXD)  (PRG) ALE  30 |------ ALE  (PRG)
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
