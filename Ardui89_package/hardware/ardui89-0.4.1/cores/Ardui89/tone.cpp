#include <tone.h>
//#define F_CPU 11059200
// Variables globales pour contrôler la PWM via l'interruption
unsigned char _89_pwm0_pin; // Broche de sortie pour le PWM
unsigned long _89_pwm0_cycles; // Nombre de cycles à exécuter
unsigned int _89_pwm0_half_period; // Demi-période du signal PWM
unsigned int _89_pwm0_current_cycle; // Compteur de cycles
unsigned int _89_pwm0_reload_value;
//unsigned char _89_pwm0_pin_state_off; // State pin when off
// Timer 0 Interruption vector
void timer0_isr(void) __interrupt (1) {
    static unsigned char toggle = LOW; // Pour alterner entre état haut et bas de la PWM

    if (_89_pwm0_current_cycle >= _89_pwm0_cycles) {
//        _89_tone_stop(_89_pwm0_pin, _89_pwm0_pin_state_off);
        noTone(_89_pwm0_pin);
        return;
    }
    toggle = !toggle;             // Alterne l'état
    digitalWrite(_89_pwm0_pin, toggle); // Écrit l'état sur la broche

    if (!toggle) {
        _89_pwm0_current_cycle++; // Incrémente le cycle seulement à l'état bas
    }

    // Charger TH0 et TL0 pour le Timer 0
    TH0 = _89_pwm0_reload_value >> 8;
    TL0 = _89_pwm0_reload_value & 0xFF;
}
void _89_tone_play(unsigned char pin, unsigned int freq, unsigned int duration_ms) {
    // Calcul de la demi-période (en cycles d'horloge) pour la fréquence souhaitée
    _89_pwm0_reload_value = 65536 - (11059200UL / (12UL * 2UL * freq));
    
    // Ajustement pour les variations de fréquence si nécessaire
    #ifndef _STC89_ADJUST_TONE_
    #define _STC89_ADJUST_TONE_ 200 / 3000
    #endif
    _89_pwm0_reload_value -= freq * _STC89_ADJUST_TONE_;
    
    _89_pwm0_cycles = (duration_ms * 1000UL) / (1000000UL / freq); // Nombre de cycles haut/bas
    _89_pwm0_current_cycle = 0;
    _89_pwm0_pin = pin;

    // Configurer le Timer 0 en mode 1 (16 bits)
    TMOD &= 0xF0; // Efface la configuration du Timer 0
    TMOD |= 0x01; // Configure le Timer 0 en mode 1

    // Charger TH0 et TL0 pour le Timer 0
    TH0 = _89_pwm0_reload_value >> 8;
    TL0 = _89_pwm0_reload_value & 0xFF;

    // Activer les interruptions
    ET0 = 1; // Activer l'interruption Timer 0
    EA = 1;  // Activer les interruptions globales
    TR0 = 1; // Démarrer le Timer 0
}

//void _89_tone_stop(unsigned char pin, unsigned char state) {
void noTone(unsigned char pin) {
   TR0 = 0; // Arrête le Timer 0
//   digitalWrite(pin, state);   // Met la broche à state (LOW/HIGH) pour désactiver le signal
   pinMode(pin, INPUT);
   TF0 = 0; // Réinitialise le drapeau de débordement
}
// tone : pin, freq, duration option, state when off (LOW/HIGH) option
void tone(unsigned char pin, unsigned int freq, ...) {
    va_list args;
    va_start(args, freq);
    unsigned int duration = (unsigned int) va_arg(args, int);
    if (duration <= 0) duration = 100; // Par défaut, 100 ms
//  unsigned char state = va_arg(args, unsigned char);
//  if (state <= 0) state = LOW;
//  _89_pwm0_pin_state_off = state;
    pinMode(pin, OUTPUT);
    _89_tone_play(pin, freq, duration);
    va_end(args);
}
/*
// noTone : pin, sate when off (LOW/HIGH) option
void noTone(unsigned char pin, ...) {
    va_list args;
    va_start(args, pin);

    unsigned char state = va_arg(args, unsigned char);
    if (state <= 0) state = LOW;

    _89_tone_stop(pin, state);

    va_end(args);
}
*/
