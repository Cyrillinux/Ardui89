/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */

#ifndef _89_MAIN_H_
#define _89_MAIN_H_

#ifdef _89C53_
// Special setup for any variants > 89C52
extern void _stc89_variant_setup(void);
#endif

// Prototypes
extern void setup(void);
extern void loop(void);

#endif
