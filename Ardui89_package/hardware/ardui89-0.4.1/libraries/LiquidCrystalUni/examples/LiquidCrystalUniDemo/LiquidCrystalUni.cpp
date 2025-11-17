#include "LiquidCrystalUni.h"

#include "Arduino.h"

#if defined(ARDUINO_ARCH_8051)
#include <8051/pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

unsigned char LiquidCrystal__rs_pin; // LOW: command.  HIGH: character.
unsigned char LiquidCrystal__rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
unsigned char LiquidCrystal__enable_pin; // activated by a HIGH pulse.
  
unsigned char LiquidCrystal__data_pins[8];

unsigned char LiquidCrystal__displayfunction;
unsigned char LiquidCrystal__displaycontrol;
unsigned char LiquidCrystal__displaymode;

unsigned char LiquidCrystal__initialized;

unsigned char LiquidCrystal__numlines;
unsigned char LiquidCrystal__row_offsets[4];

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

/*
void LiquidCrystal_LiquidCrystal(unsigned char rs, unsigned char rw, unsigned char enable,
           unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3,
           unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7)
{
  init(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

void LiquidCrystal_LiquidCrystal(unsigned char rs, unsigned char enable,
           unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3,
           unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7)
{
  init(0, rs, 255, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}*/

void LiquidCrystal_init(LiquidCrystal *display, unsigned char rs, unsigned char rw, unsigned char en, ...) {
    va_list args;
    va_start(args, en);
    
    // Fonctions d'initialisation et de contrôle de base
    display->begin = LiquidCrystal_begin;
    display->clear = LiquidCrystal_clear;
    display->home = LiquidCrystal_home;
    display->noDisplay = LiquidCrystal_noDisplay;
    display->display = LiquidCrystal_display;
    display->noBlink = LiquidCrystal_noBlink;
    display->blink = LiquidCrystal_blink;
    display->noCursor = LiquidCrystal_noCursor;
    display->cursor = LiquidCrystal_cursor;
    
    // Fonctions de défilement et de direction
    display->scrollDisplayLeft = LiquidCrystal_scrollDisplayLeft;
    display->scrollDisplayRight = LiquidCrystal_scrollDisplayRight;
    display->leftToRight = LiquidCrystal_leftToRight;
    display->rightToLeft = LiquidCrystal_rightToLeft;
    display->autoscroll = LiquidCrystal_autoscroll;
    display->noAutoscroll = LiquidCrystal_noAutoscroll;
    
    // Fonctions de configuration et d'écriture
    display->setRowOffsets = LiquidCrystal_setRowOffsets;
    display->createChar =  LiquidCrystal_createChar;
    display->setCursor = LiquidCrystal_setCursor;
    display->write = LiquidCrystal_write;

    display->printString = LiquidCrystal_printString;
    display->print = LiquidCrystal_printf;
    display->printf = LiquidCrystal_printf;
    
    /*
    // Fonctions de bas niveau
    display->command = LiquidCrystal_command;
    display->send = LiquidCrystal_send;
    display->write4bits = LiquidCrystal_write4bits;
    display->write8bits = LiquidCrystal_write8bits;
    display->pulseEnable = LiquidCrystal_pulseEnable;
    */

    LiquidCrystal__rs_pin = rs;
    LiquidCrystal__rw_pin = rw;
    LiquidCrystal__enable_pin = en;

    unsigned char d;
    int i = 0;
  
    // Continuer jusqu'à la sentinelle (par exemple 255)
    while ((d = (unsigned char)va_arg(args, int)) != NULL) {
        LiquidCrystal__data_pins[i] = d;
        i++;
    }
    if (i<7)
    LiquidCrystal__displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  else 
    LiquidCrystal__displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
    LiquidCrystal_begin(16, 1, LCD_5x8DOTS);  

    va_end(args);
}

void LiquidCrystal_begin(unsigned char cols, unsigned char lines, ...) {
  va_list args;
  va_start(args, lines);
  unsigned char dotsize = (unsigned char)va_arg(args, int);
  if (dotsize==NULL) dotsize=LCD_5x8DOTS;
  if (lines > 1) {
    LiquidCrystal__displayfunction |= LCD_2LINE;
  }
  LiquidCrystal__numlines = lines;

  LiquidCrystal_setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);  

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
    LiquidCrystal__displayfunction |= LCD_5x10DOTS;
  }

  pinMode(LiquidCrystal__rs_pin, OUTPUT);
  // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
  if (LiquidCrystal__rw_pin != 255) { 
    pinMode(LiquidCrystal__rw_pin, OUTPUT);
  }
  pinMode(LiquidCrystal__enable_pin, OUTPUT);
  
  // Do these once, instead of every time a character is drawn for speed reasons.
  for (int i=0; i<((LiquidCrystal__displayfunction & LCD_8BITMODE) ? 8 : 4); ++i)
  {
    pinMode(LiquidCrystal__data_pins[i], OUTPUT);
   } 

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
  delayMicroseconds(50000); 
  // Now we pull both RS and R/W low to begin commands
  digitalWrite(LiquidCrystal__rs_pin, LOW);
  digitalWrite(LiquidCrystal__enable_pin, LOW);
  if (LiquidCrystal__rw_pin != 255) { 
    digitalWrite(LiquidCrystal__rw_pin, LOW);
  }
  
  //put the LCD into 4 bit or 8 bit mode
  if (! (LiquidCrystal__displayfunction & LCD_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    LiquidCrystal_write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms

    // second try
    LiquidCrystal_write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms
    
    // third go!
    LiquidCrystal_write4bits(0x03); 
    delayMicroseconds(150);

    // finally, set to 4-bit interface
    LiquidCrystal_write4bits(0x02); 
  } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    LiquidCrystal_command(LCD_FUNCTIONSET | LiquidCrystal__displayfunction);
    delayMicroseconds(4500);  // wait more than 4.1ms

    // second try
    LiquidCrystal_command(LCD_FUNCTIONSET | LiquidCrystal__displayfunction);
    delayMicroseconds(150);

    // third go
    LiquidCrystal_command(LCD_FUNCTIONSET | LiquidCrystal__displayfunction);
  }

  // finally, set # lines, font size, etc.
  LiquidCrystal_command(LCD_FUNCTIONSET | LiquidCrystal__displayfunction);  

  // turn the display on with no cursor or blinking default
  LiquidCrystal__displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  LiquidCrystal_display();

  // clear it off
  LiquidCrystal_clear();

  // Initialize to default text direction (for romance languages)
  LiquidCrystal__displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  LiquidCrystal_command(LCD_ENTRYMODESET | LiquidCrystal__displaymode);

}

void LiquidCrystal_setRowOffsets(int row0, int row1, int row2, int row3)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
{
  LiquidCrystal__row_offsets[0] = row0;
  LiquidCrystal__row_offsets[1] = row1;
  LiquidCrystal__row_offsets[2] = row2;
  LiquidCrystal__row_offsets[3] = row3;
}

/********** high level commands, for the user! */
void LiquidCrystal_clear()
{
  LiquidCrystal_command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_home()
{
  LiquidCrystal_command(LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_setCursor(unsigned char col, unsigned char row)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
{
  const unsigned char max_lines = sizeof(LiquidCrystal__row_offsets) / sizeof(*LiquidCrystal__row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= LiquidCrystal__numlines ) {
    row = LiquidCrystal__numlines - 1;    // we count rows starting w/0
  }
  
  LiquidCrystal_command(LCD_SETDDRAMADDR | (col + LiquidCrystal__row_offsets[row]));
}

// Turn the display on/off (quickly)
void LiquidCrystal_noDisplay() {
  LiquidCrystal__displaycontrol &= ~LCD_DISPLAYON;
  LiquidCrystal_command(LCD_DISPLAYCONTROL | LiquidCrystal__displaycontrol);
}
void LiquidCrystal_display() {
  LiquidCrystal__displaycontrol |= LCD_DISPLAYON;
  LiquidCrystal_command(LCD_DISPLAYCONTROL | LiquidCrystal__displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_noCursor() {
  LiquidCrystal__displaycontrol &= ~LCD_CURSORON;
  LiquidCrystal_command(LCD_DISPLAYCONTROL | LiquidCrystal__displaycontrol);
}
void LiquidCrystal_cursor() {
  LiquidCrystal__displaycontrol |= LCD_CURSORON;
  LiquidCrystal_command(LCD_DISPLAYCONTROL | LiquidCrystal__displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_noBlink() {
  LiquidCrystal__displaycontrol &= ~LCD_BLINKON;
  LiquidCrystal_command(LCD_DISPLAYCONTROL | LiquidCrystal__displaycontrol);
}
void LiquidCrystal_blink() {
  LiquidCrystal__displaycontrol |= LCD_BLINKON;
  LiquidCrystal_command(LCD_DISPLAYCONTROL | LiquidCrystal__displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_scrollDisplayLeft(void) {
  LiquidCrystal_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_scrollDisplayRight(void) {
  LiquidCrystal_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_leftToRight(void) {
  LiquidCrystal__displaymode |= LCD_ENTRYLEFT;
  LiquidCrystal_command(LCD_ENTRYMODESET | LiquidCrystal__displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_rightToLeft(void) {
  LiquidCrystal__displaymode &= ~LCD_ENTRYLEFT;
  LiquidCrystal_command(LCD_ENTRYMODESET | LiquidCrystal__displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_autoscroll(void) {
  LiquidCrystal__displaymode |= LCD_ENTRYSHIFTINCREMENT;
  LiquidCrystal_command(LCD_ENTRYMODESET | LiquidCrystal__displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_noAutoscroll(void) {
  LiquidCrystal__displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  LiquidCrystal_command(LCD_ENTRYMODESET | LiquidCrystal__displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_createChar(unsigned char location, unsigned char charmap[])
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
{
  location &= 0x7; // we only have 8 locations 0-7
  LiquidCrystal_command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    LiquidCrystal_write(charmap[i]);
  }
}

// Print a string to the LCD
void LiquidCrystal_printString(const char* str)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
{
  if (str == NULL) return;  // Protection contre les pointeurs null
  
  while (*str) {
    LiquidCrystal_write(*str);
    str++;
  }
}

void LiquidCrystal_printf(const char *format, ...)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
{
  va_list args;
  va_start(args, format);

  char  _89_uart_buffer[16];
  char *str;
  int num;

  while (*format) {
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'c':
          LiquidCrystal_write(va_arg(args, int));
          break;
        case 's':
          str = (char *) va_arg(args, char *);
          LiquidCrystal_printString(str);
          break;
        case 'd':
          num = va_arg(args, int);
#if defined(ARDUINO_ARCH_8051)
          int_to_string(num, _89_uart_buffer);
#else          
          sprintf(_89_uart_buffer, "%d", num);
#endif
          LiquidCrystal_printString( _89_uart_buffer);
          break;
        default:
          LiquidCrystal_write(*format);
          break;
      }
    } else {
      LiquidCrystal_write(*format);
    }
    format++;
  }
  va_end(args);
}

/*********** mid level commands, for sending data/cmds */

void LiquidCrystal_command(unsigned char value)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
{
  LiquidCrystal_send(value, LOW);
}

unsigned char LiquidCrystal_write(unsigned char value)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
{
  LiquidCrystal_send(value, HIGH);
  return 1; // assume sucess
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void LiquidCrystal_send(unsigned char value, unsigned char mode) {
  digitalWrite(LiquidCrystal__rs_pin, mode);

  // if there is a RW pin indicated, set it low to Write
  if (LiquidCrystal__rw_pin != 255) { 
    digitalWrite(LiquidCrystal__rw_pin, LOW);
  }
  
  if (LiquidCrystal__displayfunction & LCD_8BITMODE) {
    LiquidCrystal_write8bits(value); 
  } else {
    LiquidCrystal_write4bits(value>>4);
    LiquidCrystal_write4bits(value);
  }
}

void LiquidCrystal_pulseEnable(void) {
  digitalWrite(LiquidCrystal__enable_pin, LOW);
  delayMicroseconds(1);    
  digitalWrite(LiquidCrystal__enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(LiquidCrystal__enable_pin, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
}

void LiquidCrystal_write4bits(unsigned char value) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LiquidCrystal__data_pins[i], (value >> i) & 0x01);
  }

  LiquidCrystal_pulseEnable();
}

void LiquidCrystal_write8bits(unsigned char value) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(LiquidCrystal__data_pins[i], (value >> i) & 0x01);
  }
  
  LiquidCrystal_pulseEnable();
}