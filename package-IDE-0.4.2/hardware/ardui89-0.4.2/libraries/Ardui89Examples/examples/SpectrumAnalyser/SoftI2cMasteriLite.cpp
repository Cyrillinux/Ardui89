/* SoftI2cMasterUniLite - Version Ultra-Lite pour STC15
 * Plus de structures, plus d'arguments : accès direct aux registres.
 * Cyril BARBATO 2026
 */
#include "SoftI2cMasterLite.h"

// Hardware Fixe
#ifndef SDA
#define SDA P1_4
#endif
#ifndef SCL
#define SCL P1_5
#endif


void SoftI2cMaster_init(void) {
    SCL = 1;
    SDA = 1;
}

unsigned char SoftI2cMaster_start(unsigned char addr) {
    SDA = 0;
    SCL = 0;
    return SoftI2cMaster_write(addr);
}

void SoftI2cMaster_stop(void) {
    SDA = 0;
    SCL = 1;
    SDA = 1;
}

unsigned char SoftI2cMaster_write(unsigned char b) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SDA = (b & 0x80) ? 1 : 0;
        SCL = 1; SCL = 0;
        b <<= 1;
    }
    SDA = 1; SCL = 1;
    i = SDA; SCL = 0;
    return (i == 0);
}
