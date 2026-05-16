/* SoftI2cMasterUni based On Arduino SoftI2cMaster Library
 * Copyright (C) 2025 by Cyril BARBATO
 * Copyright (C) 2009 by William Greiman
 *
 * This file is part of the Arduino SoftI2cMaster Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino SoftI2cMaster Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include "SoftI2cMasterUni.h"
//------------------------------------------------------------------------------
// WARNING don't change anything unless you verify the change with a scope
//------------------------------------------------------------------------------
// init pins and set bus high

SoftI2cMaster *_i2cmastersel=NULL;

void SoftI2cMaster_init(SoftI2cMaster *wire, unsigned char sclPin, unsigned char sdaPin)
{
  _i2cmastersel=wire;
  wire->start=_SoftI2cMaster_start;
  wire->restart=_SoftI2cMaster_restart;
  wire->stop=_SoftI2cMaster_stop;
  wire->read=_SoftI2cMaster_read;
  wire->write=_SoftI2cMaster_write;
  wire->sclPin_ = sclPin;
  wire->sdaPin_ = sdaPin;
  pinMode(wire->sclPin_, OUTPUT);
  pinMode(wire->sdaPin_, OUTPUT);
  digitalWrite(wire->sclPin_, HIGH);
  digitalWrite(wire->sdaPin_, HIGH);
}
//------------------------------------------------------------------------------
// read a byte and send Ack if last is false else Nak to terminate read
unsigned char SoftI2cMaster_read(SoftI2cMaster *wire, unsigned char last)
{
  unsigned char b = 0;
  // make sure pullup enabled
  digitalWrite(wire->sdaPin_, HIGH);
  pinMode(wire->sdaPin_, INPUT);
  // read byte
  for (unsigned char i = 0; i < 8; i++) {
    // don't change this loop unless you verify the change with a scope
    b <<= 1;
#ifndef ARDUINO_ARCH_8051
    delayMicroseconds(I2C_DELAY_USEC);
#endif
    digitalWrite(wire->sclPin_, HIGH);
    if (digitalRead(wire->sdaPin_)) b |= 1;
    digitalWrite(wire->sclPin_, LOW);
  }
  // send Ack or Nak
  pinMode(wire->sdaPin_, OUTPUT);
  digitalWrite(wire->sdaPin_, last);
  digitalWrite(wire->sclPin_, HIGH);
#ifndef ARDUINO_ARCH_8051
    delayMicroseconds(I2C_DELAY_USEC);
#endif
  digitalWrite(wire->sclPin_, LOW);
  digitalWrite(wire->sdaPin_, HIGH);
  return b;
}
//------------------------------------------------------------------------------
// send new address and read/write without stop
unsigned char SoftI2cMaster_restart(SoftI2cMaster *wire, unsigned char addressRW)
{
  digitalWrite(wire->sclPin_, HIGH);
  return SoftI2cMaster_start(wire, addressRW);
}
//------------------------------------------------------------------------------
// issue a start condition for i2c address with read/write bit
unsigned char SoftI2cMaster_start(SoftI2cMaster *wire, unsigned char addressRW)
{
  digitalWrite(wire->sdaPin_, LOW);
#ifndef ARDUINO_ARCH_8051
    delayMicroseconds(I2C_DELAY_USEC);
#endif
  digitalWrite(wire->sclPin_, LOW);
  return SoftI2cMaster_write(wire, addressRW);
}
//------------------------------------------------------------------------------
// issue a stop condition
void SoftI2cMaster_stop(SoftI2cMaster *wire)
{
#ifndef ARDUINO_ARCH_8051
    delayMicroseconds(I2C_DELAY_USEC);
#endif
  digitalWrite(wire->sdaPin_, LOW);
  digitalWrite(wire->sclPin_, HIGH);
#ifndef ARDUINO_ARCH_8051
    delayMicroseconds(I2C_DELAY_USEC);
#endif
  digitalWrite(wire->sdaPin_, HIGH);
#ifndef ARDUINO_ARCH_8051
    delayMicroseconds(I2C_DELAY_USEC);
#endif
}
//------------------------------------------------------------------------------
// write byte and return true for Ack or false for Nak
unsigned char SoftI2cMaster_write(SoftI2cMaster *wire, unsigned char b)
{
  // write byte
  for (unsigned char m = 0X80; m != 0; m >>= 1) {
    // don't change this loop unless you verivy the change with a scope
    digitalWrite(wire->sdaPin_, m & b);
    digitalWrite(wire->sclPin_, HIGH);
#ifndef ARDUINO_ARCH_8051
    delayMicroseconds(I2C_DELAY_USEC);
#endif
    digitalWrite(wire->sclPin_, LOW);
  }
  // get Ack or Nak
  digitalWrite(wire->sdaPin_, HIGH);
  pinMode(wire->sdaPin_, INPUT);
  digitalWrite(wire->sclPin_, HIGH);
  b = digitalRead(wire->sdaPin_);
  digitalWrite(wire->sclPin_, LOW);
  pinMode(wire->sdaPin_, OUTPUT);
  return b == 0;
}

// Linking
//------------------------------------------------------------------------------
// issue a start condition for i2c address with read/write bit
unsigned char _SoftI2cMaster_start(unsigned char addressRW)
{
  return SoftI2cMaster_start(_i2cmastersel, addressRW);
}
//------------------------------------------------------------------------------
// send new address and read/write without stop
unsigned char _SoftI2cMaster_restart(unsigned char addressRW)
{
  return SoftI2cMaster_restart(_i2cmastersel, addressRW);
}
//------------------------------------------------------------------------------
// issue a stop condition
void _SoftI2cMaster_stop(void)
{
 SoftI2cMaster_stop(_i2cmastersel);
}
//------------------------------------------------------------------------------
// send new address and read/write without stop
unsigned char _SoftI2cMaster_read(unsigned char last)
{
  return SoftI2cMaster_read(_i2cmastersel, last);
}
//------------------------------------------------------------------------------
// write byte and return true for Ack or false for Nak
unsigned char _SoftI2cMaster_write(unsigned char b)
{
  return SoftI2cMaster_write(_i2cmastersel, b);
}
