#ifndef LiquidCrystalC_h
#define LiquidCrystalC_h

#define LCD_NORW  255

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

typedef struct _LiquidCrystal {
    // Fonctions d'initialisation et de contrôle de base
    void (*begin)(unsigned char cols, unsigned char lines, ...);
    void (*clear)(void);
    void (*home)(void);
    void (*noDisplay)(void);
    void (*display)(void);
    void (*noBlink)(void);
    void (*blink)(void);
    void (*noCursor)(void);
    void (*cursor)(void);
    
    // Fonctions de défilement et de direction
    void (*scrollDisplayLeft)(void);
    void (*scrollDisplayRight)(void);
    void (*leftToRight)(void);
    void (*rightToLeft)(void);
    void (*autoscroll)(void);
    void (*noAutoscroll)(void);
    
    // Fonctions de configuration et d'écriture
    void (*setRowOffsets)(int row1, int row2, int row3, int row4)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
    void (*createChar)(unsigned char location, unsigned char charmap[])
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
    void (*setCursor)(unsigned char col, unsigned char row)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
    unsigned char (*write)(unsigned char value)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
    void (*printString)(const char* str)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
    void (*print)(const char *format, ...)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
    void (*printf)(const char *format, ...)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
   
    /*
    // Fonctions de bas niveau
    void (*command)(unsigned char value);
    void (*send)(unsigned char value, unsigned char mode);
    void (*write4bits)(unsigned char value);
    void (*write8bits)(unsigned char value);
    void (*pulseEnable)(void);
    */
    
} LiquidCrystal;

/*
  LiquidCrystal(unsigned char rs, unsigned char enable,
    unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3,
    unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7);
  LiquidCrystal(unsigned char rs, unsigned char rw, unsigned char enable,
    unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3,
    unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7);
  LiquidCrystal(unsigned char rs, unsigned char rw, unsigned char enable,
    unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3);
  LiquidCrystal(unsigned char rs, unsigned char enable,
    unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3);
*/
  void LiquidCrystal_init(LiquidCrystal *display, unsigned char rs, unsigned char rw, unsigned char en, ...);
  void LiquidCrystal_begin(unsigned char cols, unsigned char lines, ...);
  void LiquidCrystal_clear();
  void LiquidCrystal_home();

  void LiquidCrystal_noDisplay();
  void LiquidCrystal_display();
  void LiquidCrystal_noBlink();
  void LiquidCrystal_blink();
  void LiquidCrystal_noCursor();
  void LiquidCrystal_cursor();
  void LiquidCrystal_scrollDisplayLeft();
  void LiquidCrystal_scrollDisplayRight();
  void LiquidCrystal_leftToRight();
  void LiquidCrystal_rightToLeft();
  void LiquidCrystal_autoscroll();
  void LiquidCrystal_noAutoscroll();

  void LiquidCrystal_setRowOffsets(int row1, int row2, int row3, int row4)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
  void LiquidCrystal_createChar(unsigned char location, unsigned char charmap[])
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
  void LiquidCrystal_setCursor(unsigned char value, unsigned char mode)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
; 
  unsigned char LiquidCrystal_write(unsigned char value)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
  void LiquidCrystal_command(unsigned char value)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
  
  void LiquidCrystal_printString(const char *str)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;
  void LiquidCrystal_printf(const char *format, ...)
#if defined(ARDUINO_ARCH_8051)
__reentrant
#endif
;


  // Internal
  void LiquidCrystal_send(unsigned char, unsigned char);
  void LiquidCrystal_write4bits(unsigned char);
  void LiquidCrystal_write8bits(unsigned char);
  void LiquidCrystal_pulseEnable();  

  extern unsigned char LiquidCrystal__rs_pin; // LOW: command.  HIGH: character.
  extern unsigned char LiquidCrystal__rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
  extern unsigned char LiquidCrystal__enable_pin; // activated by a HIGH pulse.
  
  extern unsigned char LiquidCrystal__data_pins[8];

  extern unsigned char LiquidCrystal__displayfunction;
  extern unsigned char LiquidCrystal__displaycontrol;
  extern unsigned char LiquidCrystal__displaymode;

  extern unsigned char LiquidCrystal__initialized;

  extern unsigned char LiquidCrystal__numlines;
  extern unsigned char LiquidCrystal__row_offsets[4];

#endif