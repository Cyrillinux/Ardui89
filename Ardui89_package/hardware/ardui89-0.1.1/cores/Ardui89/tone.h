#include <Arduino.h>
#include <stdarg.h>
extern unsigned char _pwm0_pin;
// Fonction pour activer le signal PWM
void _pwm0_start(unsigned int freq);
// play tone
void _tone_play(unsigned int freq, unsigned int duration);
// Fonction pour désactiver le signal PWM
void noTone(unsigned char pin);
// tone
void tone(unsigned char pin, unsigned int freq, ...);
