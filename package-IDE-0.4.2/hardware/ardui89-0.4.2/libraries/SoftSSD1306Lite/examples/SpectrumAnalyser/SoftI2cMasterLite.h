/* SoftI2cMasterUniLite - Version Ultra-Lite pour STC15
 * Plus de structures, plus d'arguments : accès direct aux registres.
 * Cyril BARBATO 2026
 */
#ifndef SOFT_I2C_MASTER_LITE
#define SOFT_I2C_MASTER_LITE

#include <8051.h>

// Initialise les pins P1.0 (SCL) et P1.1 (SDA)
void SoftI2cMaster_init(void);

// Envoie une condition de START + Adresse (addr est déjà décalée avec R/W)
unsigned char SoftI2cMaster_start(unsigned char addr);

// Envoie une condition de STOP
void SoftI2cMaster_stop(void);

// Écrit un octet brut sur le bus. Retourne 1 si ACK, 0 si NACK.
unsigned char SoftI2cMaster_write(unsigned char b);

// Lit un octet. last=0 pour ACK, last=1 pour NACK.
unsigned char SoftI2cMaster_read(unsigned char last);

#endif
