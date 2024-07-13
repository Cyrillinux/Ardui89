# Ardui89 C IDE Beta 0.1.0
Under GPL license

Arduino for 8051 family (STC89C51; STC89C52, STC15F2K32S2...)

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

