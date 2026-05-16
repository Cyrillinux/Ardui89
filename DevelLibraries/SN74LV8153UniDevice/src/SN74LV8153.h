/*
Copyright (c) 2024, github.com/macafeeje
All rights reserved.

This source code is licensed under the GNUv3.0-style license found in the
LICENSE file in the root directory of this source tree. 
*/

//chip datasheet - https://www.ti.com/lit/ds/symlink/sn74lv8153.pdf
//one wire serial to parallel data converter

#pragma once

class S2PI{

private:
  uint8_t serial_pin = 0xff;               //arduino pin number
  uint8_t reset_pin = 0xff;                //arduino pin number

  unsigned long data_delay = 40;           //delay time between bits (Arduino UNO; this is about 22.2kbps


public:
  void S2PI_decoder(){
    
  }

public:
  void S2PI_decoder(const uint8_t serial, const uint8_t reset){
    //optional constructor

    begin(serial, reset);
  }

public:
  void begin(const uint8_t serial, const uint8_t reset){
    //configure serial and reset pins, then reset the chip

    serial_pin = serial;
    reset_pin = reset;

    pinMode(serial_pin, OUTPUT);
    pinMode(reset_pin, OUTPUT);
    
    digitalWrite(reset_pin, LOW);
    digitalWrite(serial_pin, HIGH);
  }

public:
  void reset(){
    //resets the chip

    if (not_setup()){
      return;
    }
    begin(serial_pin, reset_pin);
  }

public:
  void output(const uint8_t device_addr, const uint8_t data){

    //@24kbps max, digitalWrite should be fast enough
    //two frames contain the start bits, address bits, data bits and stop bits required to communicate over 1 wire serial interface

    //frame data structure;
    //[      unused      ][                 FRAME                  ]
    // x  x  x  x   x  x  1   x    x   x   x   x    x   x   1   0
    //[0][0][0][0] [0][0][SP][D3] [D2][D1][D0][A2] [A1][A0][S1][S0]
    //[0][0][0][0] [0][0][SP][D7] [D6][D5][D4][A2] [A1][A0][S1][S0]
    //read out LSB to MSB

    if (not_setup()){
      return;
    }
    
    digitalWrite(reset_pin, HIGH);
    digitalWrite(serial_pin, HIGH);
    
    uint16_t frame[2] = {0x202};                                    //create empty serial frames

    frame[0] |= (device_addr & 0x07) << 2;                          //add start, address and stop bits to frame
    frame[1] = frame[0];

    frame[0] |= (data & 0x0f) << 5;                                 //add data bits to frames
    frame[1] |= (data & 0xf0) << 1;
    
    //serial output the 2 frames; LSB -> MSB, 10 bits per frame
    uint8_t frame_no = 0;
    uint16_t mask = 1;
    noInterrupts();

    for (int l = 0; l < 20; l++){
      //write the serial pin HIGH or LOW based on a masked bit position and the current frame number
      if ((frame[frame_no] & mask) == 0){
        digitalWrite(serial_pin, LOW);
      }else{
        digitalWrite(serial_pin, HIGH);
      }

      //unregulated delay
      delayMicroseconds(data_delay);

      //update bit mask position and frame number
      mask = mask << 1;
      if (l == 9){
        frame_no++;
        mask = 1;
      }
    }

    interrupts();
  }

private:
  bool not_setup(){
    //crude method of checking the begin() method has been called to assign pins

    if (serial_pin == 0xff && reset_pin == 0xff){
      return true;
    }
    return false;
  }

};
