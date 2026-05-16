// Universal LiquidCrystal Library example
// 8051 and AVR arch

// include the library code
#include "LiquidCrystalUni.h"

// LCD object
LiquidCrystal lcd;

// special chars (icons)
#define ICON_LOCKED_CHAR   (byte)0
#define ICON_UNLOCKED_CHAR (byte)1
PROGMEM const byte iconLocked[8] = {
  0b01110,
  0b10001,
  0b10001,
  0b11111,
  0b11011,
  0b11011,
  0b11111,
};
PROGMEM const byte iconUnlocked[8] = {
  0b01110,
  0b10000,
  0b10000,
  0b11111,
  0b11011,
  0b11011,
  0b11111,
};

// Init icons function
void init_icons(LiquidCrystal *lcd) {
  unsigned char icon[8];
  memcpy_P(icon, iconLocked, sizeof(icon));
  lcd->createChar(ICON_LOCKED_CHAR, icon);
  memcpy_P(icon, iconUnlocked, sizeof(icon));
  lcd->createChar(ICON_UNLOCKED_CHAR, icon);
}

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;

unsigned int s=0;

void setup() {

  // 4 bits init and no rw
  LiquidCrystal_init(&lcd, rs, LCD_NORW, en, d4, d5, d6, d7);
  
  // IMPORTANT: Call begin() after init() for finsh configuration
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print(" Hello, world!");

  delay(3000);

  // Clear
  lcd.clear();
  
    // Print special char (icon)
  lcd.write(ICON_UNLOCKED_CHAR);

  // Print a message to the LCD.
  lcd.print(" Unlocked !");

  // Blink
  lcd.blink();

  // init special chars (icons)
  init_icons(&lcd);

}

void loop() {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
  // print the number of seconds
  lcd.print("%d",s);
  delay(1000);
  s++;
  
  if (s>9) {

    //Return to top left
    lcd.setCursor(0, 0);

    // Print special char (icon)
    lcd.write(ICON_LOCKED_CHAR);

    // Print message
    lcd.print(" Locked !     ");

    // No Blink
    lcd.noBlink();

  }

}
