/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2025
 */
#include <8051/pgmspace.h>
// memcpy_P
void memcpy_P(unsigned char *dest, const unsigned char __code *src, unsigned int len) {
    while (len--) {
        *dest++ = *src++;
    }
}
