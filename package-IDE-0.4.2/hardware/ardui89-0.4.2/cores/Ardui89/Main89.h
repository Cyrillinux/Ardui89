/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024-2026
 */

#ifndef _89_MAIN_H_
#define _89_MAIN_H_

#define int8_t char
#define int16_t int
#define uint8_t unsigned char
#define uint16_t unsigned int

#define _nop_() __asm__("nop")

#ifdef _89C53_
// Special setup for any variants > 89C52
extern void _stc89_variant_setup(void);
#endif

// Prototypes
extern void setup(void);
extern void loop(void);

#endif
