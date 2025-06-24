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
#include <Arduino.h>

#ifndef SOFT_I2C_MASTER
#define SOFT_I2C_MASTER
//#include "TwoWireBase.h"

// delay used to tweek signals
#define I2C_DELAY_USEC 4

typedef struct _TwoWireBase {
    unsigned char sclPin_;
    unsigned char sdaPin_;
    unsigned char (*write)(unsigned char b);
    unsigned char (*start)(unsigned char addressRW);
    unsigned char (*restart)(unsigned char addressRW);
    void (*stop)(void);
    unsigned char (*read)(unsigned char last);

} SoftI2cMaster;

extern SoftI2cMaster *_i2cmastersel;

  /** init bus */
  void SoftI2cMaster_init(SoftI2cMaster *wire, unsigned char sclPin, unsigned char sdaPin);
  
  /** read a byte and send Ack if last is false else Nak to terminate read */
  unsigned char SoftI2cMaster_read(SoftI2cMaster *wire, unsigned char last);
  
  /** send new address and read/write bit without stop */
  unsigned char SoftI2cMaster_restart(SoftI2cMaster *wire, unsigned char addressRW);
  
  /** issue a start condition for i2c address with read/write bit */
  unsigned char SoftI2cMaster_start(SoftI2cMaster *wire, unsigned char addressRW);
  
  /** issue a stop condition */
  void SoftI2cMaster_stop(SoftI2cMaster *wire);
  
  /** write byte and return true for Ack or false for Nak */
  unsigned char SoftI2cMaster_write(SoftI2cMaster *wire, unsigned char b);

  // Linking
  unsigned char _SoftI2cMaster_start(unsigned char addressRW);
  unsigned char _SoftI2cMaster_restart(unsigned char addressRW);
  void _SoftI2cMaster_stop(void);
  unsigned char _SoftI2cMaster_read(unsigned char last);
  unsigned char _SoftI2cMaster_write(unsigned char b);

#endif //SOFT_I2C_MASTER
