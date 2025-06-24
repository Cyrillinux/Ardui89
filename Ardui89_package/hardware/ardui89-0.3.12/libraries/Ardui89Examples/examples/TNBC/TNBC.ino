// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

#define BUZZER_PIN 27

PROGMEM int melody[] = {
  NOTE_G4,   8, NOTE_G4,   8, NOTE_G4,   8, NOTE_G4,   8, NOTE_G4,  16, NOTE_GS4, 16, NOTE_F4,   8, NOTE_F4,   4,
  NOTE_F4,  16, NOTE_F4,  16, NOTE_F4,   8, NOTE_F4,  16, NOTE_F4,  16, NOTE_F4,   8, NOTE_F4,  16, NOTE_G4,  16, NOTE_GS4,  8, NOTE_G4,   4,
  NOTE_G4,   8, NOTE_G4,   8, NOTE_G4,   8, NOTE_G4,  16, NOTE_A4,  16, NOTE_AS4,  8, NOTE_A4,  16, NOTE_G4,  16, NOTE_F4,   4,
  NOTE_F4,   8, NOTE_F4,   8, NOTE_F4,  16, NOTE_G4,  16, NOTE_GS4,  8, NOTE_G4,   8, NOTE_DS4,  8, NOTE_D4,   8, NOTE_G4,   8,
  NOTE_AS4,  8, NOTE_AS4,  8, NOTE_AS4, 16, NOTE_A4,  16, NOTE_G4,   8, NOTE_AS4,  8, NOTE_AS4,  8, NOTE_AS4, 16, NOTE_A4,  16, NOTE_G4,   8,
  NOTE_AS4,  8, NOTE_F4,   8, NOTE_F4,   8, NOTE_DS4, 16, NOTE_D4,  16, NOTE_C4,   8, NOTE_G4,   8, NOTE_A4,   4,
  NOTE_B4,   8, NOTE_B4,   8, NOTE_B4,  16, NOTE_AS4, 16, NOTE_GS4,  8, NOTE_B4,  16, NOTE_B4,  16, NOTE_B4,  16, NOTE_B4,  16, NOTE_B4,  16, NOTE_AS4, 16, NOTE_GS4,  8,
  NOTE_B4,   8, NOTE_G4,   8, NOTE_G4,   8, NOTE_FS4, 16, NOTE_E4,  16, NOTE_CS4, 16, NOTE_CS4, 16, NOTE_GS4, 16, NOTE_GS4, 16, NOTE_GS4, 16, NOTE_GS4, 16, NOTE_GS4,  8,
  NOTE_FS4,  8, NOTE_FS4,  8, NOTE_G4,   4, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_G4,   8, NOTE_FS4,  8, 
  NOTE_A3,   8, NOTE_F4,   8, NOTE_F4,   8, NOTE_A3,   8, NOTE_GS3,  8, NOTE_A3,  16, NOTE_B3,  16, NOTE_CS4,  4,
  NOTE_FS4,  8, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4,  8, NOTE_FS4,  4,
  NOTE_A4,   8, NOTE_A4,   8, NOTE_A4,   8, NOTE_A4,   8, NOTE_GS4,  8, NOTE_GS4, 16, NOTE_GS4, 16, NOTE_GS4,  4,
  NOTE_FS4,  8, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4,  8, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4,  8, NOTE_FS4,  4,
  NOTE_A4,  16, NOTE_A4,  16, NOTE_A4,   8, NOTE_A4,   8, NOTE_A4,   8, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4, 16, NOTE_FS4,  4,
  NOTE_DS4,  8, NOTE_DS4,  8, NOTE_DS4, 16, NOTE_D4,  16, NOTE_C4,   8, NOTE_DS4,  8, NOTE_DS4,  8, NOTE_DS4, 16, NOTE_D4,  16, NOTE_C4,   8,
  NOTE_B4,  16, NOTE_AS4, 16, NOTE_GS4,  8, NOTE_B4,  16, NOTE_AS4, 16, NOTE_GS4,  8, NOTE_GS4, 16, NOTE_G4,  16, NOTE_F4,   8, NOTE_GS4, 16, NOTE_G4, 16, NOTE_F4,    8,
  NOTE_F4, 1, 0
};


void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    int n;
    for (n=0;melody[n]>0;n+=2) {
      digitalWrite(8, LOW);
      tone(BUZZER_PIN, melody[n], 2000/melody[n+1]);
      delay(2000/melody[n+1]);
      noTone(BUZZER_PIN);
      digitalWrite(8, HIGH);
    }
 }
