// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

#define BUZZER_PIN 27

PROGMEM int melody[] = {
  NOTE_AS4, 8, NOTE_AS4, 8, NOTE_AS4, 8,
  NOTE_F5,  2, NOTE_C6,  2,
  NOTE_AS5, 8, NOTE_A5,  8, NOTE_G5,  8, NOTE_F6, 2, NOTE_C6, 4,
  NOTE_AS5, 8, NOTE_A5,  8, NOTE_G5,  8, NOTE_F6, 2, NOTE_C6, 4,
  NOTE_AS5, 8, NOTE_A5,  8, NOTE_AS5,  8, NOTE_G5, 2, NOTE_C5, 8, NOTE_C5, 8, NOTE_C5, 8,
  NOTE_F5,  2, NOTE_C6,  2,
  NOTE_AS5, 8, NOTE_A5,  8, NOTE_G5,  8, NOTE_F6, 2, NOTE_C6, 4,

  NOTE_AS5, 8, NOTE_A5,  8, NOTE_G5,  8, NOTE_F6, 2, NOTE_C6, 4,
  NOTE_AS5, 8, NOTE_A5,  8, NOTE_AS5, 8, NOTE_G5, 2, NOTE_C5, 8, NOTE_C5, 16,
  NOTE_D5,  4, NOTE_D5,  8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
  NOTE_F5,  8, NOTE_G5,  8, NOTE_A5,  8, NOTE_G5, 4, NOTE_D5, 8, NOTE_E5, 4, NOTE_C5, 8, NOTE_C5, 16,
  NOTE_D5,  4, NOTE_D5,  8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,

  NOTE_C6,  8, NOTE_G5, 16, NOTE_G5,  2, NOTE_C5, 8,
  NOTE_D5,  4, NOTE_D5,  8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
  NOTE_F5,  8, NOTE_G5,  8, NOTE_A5,  8, NOTE_G5, 4, NOTE_D5, 8, NOTE_E5, 4, NOTE_C6, 8, NOTE_C6, 16,
  NOTE_F6,  4, NOTE_DS6, 8, NOTE_CS6, 4, NOTE_C6, 8, NOTE_AS5, 4, NOTE_GS5, 8, NOTE_G5, 4, NOTE_F5, 8,
  NOTE_C6,  1,
  0
};

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    int n;
    for (n=0;melody[n]>0;n+=2) {
      tone(BUZZER_PIN, melody[n], 1000/melody[n+1]);
      delay(1000/melody[n+1]);
      noTone(BUZZER_PIN);
    }
 }
