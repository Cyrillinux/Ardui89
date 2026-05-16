# SN74LV8153
Arduino UNO library for Serial to Parallel Interface SN74LV8153 chip</br>
ref. datasheet: https://www.ti.com/lit/ds/symlink/sn74lv8153.pdf

</br>
Example:

```
#include "SN74LV8153.h"

S2PI decoder;
const uint8_t serial_pin = 2;
const uint8_t reset_pin = 3;
const uint8_t device_address = 0;      //set by pin programming, ref. datasheet

void setup(){
  decoder.begin(serial_pin, reset_pin);
}

void loop(){
  uint8_t data = 0xff;    //8-bit data to send to chip

  decoder.output(device_address, data);

  while(1);
}
