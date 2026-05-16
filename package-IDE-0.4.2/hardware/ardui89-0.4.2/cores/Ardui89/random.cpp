/*
 * DISLAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <random.h>
// Fonction pour tirer au sort un nombre entier compris dans un intervalle [mini, maxi]
unsigned int random(unsigned int mini, ...) {
    va_list args;
    va_start(args, mini);
    unsigned int maxi = (unsigned int) va_arg(args, int);
    if (maxi <= 0) maxi=mini*2;
    unsigned int range = maxi - mini + 1;
    unsigned int rand_num = rand() % range; // Limite le nombre aléatoire à l'intervalle
    return mini + rand_num;
}
