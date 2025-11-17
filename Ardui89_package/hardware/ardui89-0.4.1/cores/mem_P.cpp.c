/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2025
 */
#include <mem_P.h>
// memcpy_P
void memcpy_P(unsigned char *dest, const unsigned char __code *src, unsigned int len) {
    while (len--) {
        *dest++ = *src++;
    }
}
