#include <tone.h>
//#define F_CPU 11059200
unsigned char _pwm0_pin;
// Fonction pour activer le signal PWM
void _pwm0_start(unsigned  freq) {
    float adj = F_CPU / 12000000; if (adj<1) adj=1;
    // La période de comptage du timer
    float cycles_timer = 0xFFE8 * (2000/freq) * adj;
    // La valeur initiale du timer
    unsigned int valeur_timer = (unsigned int) cycles_timer;
    TMOD=0x01;  //timer0 mode1(16 bit)
    TH0 = (valeur_timer >> 8) & 0xFF;      //load TH0
    TL0 = valeur_timer & 0xFF; // TL0
    TR0 = 1; //turn on T0
    //ET0 = 1;      // Enable timer 0 interrupt
    //EA = 1;       // Enable global interrupt
    while(TF0==0); // wait for flag generation
    TR0=0;   // turn off T0
    TF0=0;    // clear TF0
}
// Fonction play
void _tone_play(unsigned int freq, unsigned int duration) {
    float repeat = duration / (1000/freq);
    for(int i=0 ; i < (int) repeat ; i++) {
        digitalWrite(_pwm0_pin, HIGH);
        _pwm0_start(freq);
        digitalWrite(_pwm0_pin, LOW);
        _pwm0_start(freq);
    }
}
// Fonction pour calculer les valeurs TL0 et TH0 en fonction de la fréquence désirée et mettre en route le timer
void tone(unsigned char pin, unsigned int freq, ...) {
    va_list args;
    va_start(args, freq);
    _pwm0_pin = pin;
    unsigned int duration = va_arg(args, unsigned int);
    if (duration <= 0) duration=100;
     _tone_play(freq, duration) ;  // les 8 bits de poids fort, les 8 bits de poids faible
    va_end(args);
}

// Fonction pour désactiver le signal PWM
void noTone(unsigned char pin) {
  TR0 = 0;  // Stopper le Timer 1
  digitalWrite(pin, LOW);  // Mettre la broche PWM à 0
}
