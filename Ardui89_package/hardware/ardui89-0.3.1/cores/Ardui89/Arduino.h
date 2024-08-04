/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */

#ifndef Arduino_h
#define Arduino_h

//#include <8051.h> // OLD Version <= 0.3
//8051, 8052 etc... in pins_arduino.h in variants path
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
/*
 **********************
 * 89 SPECIFICS PATCH *
 **********************
 */
#include <pins_arduino.h>
#include <Main89.h>
#include <delay.h>
#include <wiring_digital.h>
#include <uart_stdio.h>
#include <tone.h>
#include <random.h>
#define byte unsigned char
#define String char*
/*
 **************************
 * END 89 SPECIFICS PATCH *
 **************************
 */
//#include <pgmspace.h>
//#include <io.h>
//#include <interrupt.h>
//#include "binary.h"

#ifndef PI

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559

#endif
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts() sei()
#define noInterrupts() cli()

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

#define bit(b) (1UL << (b))


#endif
