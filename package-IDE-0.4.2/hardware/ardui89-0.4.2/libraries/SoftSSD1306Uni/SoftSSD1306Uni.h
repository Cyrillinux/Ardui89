#include "SoftI2cMasterUni.h"
#define SSD1306_I2C_ADDRESS 0x3C
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

// Commandes du SSD1306
#define SSD1306_COMMAND 0x00
#define SSD1306_DATA 0x40

static unsigned char cursorX = 0;
static unsigned char cursorY = 0;

typedef struct _SSD1306 {
    SoftI2cMaster *wire;
    void (*clear)(void);
    void (*setCursor)(unsigned char, unsigned char);
    void (*print)(const char *);
    void (*println)(const char *);
    void (*printChar)(unsigned char);
} SSD1306;

extern SSD1306 *_ssd1306sel;

    void SSD1306_sendCommand(SoftI2cMaster *wire, unsigned char command);

    void SSD1306_sendData(SoftI2cMaster *wire, unsigned char data);
  
    void SSD1306_init(SSD1306 *display, SoftI2cMaster *wire);

    void SSD1306_clear(SoftI2cMaster *wire);

    void SSD1306_setCursor(SoftI2cMaster *wire, unsigned char x, unsigned char y);

    void SSD1306_print(SoftI2cMaster *wire, const char* text);

    void SSD1306_println(SoftI2cMaster *wire, const char* text);

    void SSD1306_writeChar(SoftI2cMaster *wire, unsigned char c);

// Linking
    void _SSD1306_clear(void);
    void _SSD1306_setCursor(unsigned char x, unsigned char y);
    void _SSD1306_print(const char* text);
    void _SSD1306_println(const char* text);
    void _SSD1306_writeChar(unsigned char c);