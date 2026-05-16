// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

#define BUZZER_PIN 27

PROGMEM int melody[] = {
  NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 4,
  NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 4,
  NOTE_E5, 8, NOTE_G5, 8, NOTE_C5, 8, NOTE_D5, 8,
  NOTE_E5, 2,
  NOTE_F5, 8, NOTE_F5, 8, NOTE_F5, 8, NOTE_F5, 8,
  NOTE_F5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 16, NOTE_E5, 16,
  NOTE_E5, 8, NOTE_D5, 8, NOTE_D5, 8, NOTE_E5, 8,
  NOTE_D5, 4, NOTE_G5, 4,
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
