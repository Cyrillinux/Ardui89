/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024-2026
 * Last revision : 2026/05/14 0.4.2
 */
// ============================================================
// --- RACINE CARRÉE 8 bits (évite d'inclure math.h) ---
// ============================================================
unsigned char sqrt8(unsigned int n) {
    unsigned char res = 0, bit = 0x80;
    while (bit > 0) {
        unsigned char temp = res + bit;
        if ((unsigned int)temp * temp <= n) res = temp;
        bit >>= 1;
    }
    return res;
}
