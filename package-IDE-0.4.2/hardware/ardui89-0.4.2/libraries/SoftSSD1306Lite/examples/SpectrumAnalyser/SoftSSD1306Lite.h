/* SoftSSD1306UniLite - Version Ultra-Lite pour STC15
 * Gestion de l'affichage OLED 128x64 sans surcharge mémoire.
 * Cyril BARBATO 2026
 */
#ifndef SOFT_SSD1306_LITE
#define SOFT_SSD1306_LITE

// Configuration de l'écran
#define SSD1306_I2C_ADDRESS 0x78  // (0x3C << 1)
#define SSD1306_WIDTH       128
#define SSD1306_HEIGHT      64

// Variables globales pour le suivi du texte (définies dans le .cpp)
extern unsigned char cursorX;
extern unsigned char cursorY;

// --- API Publique ---

// Initialise le bus I2C et l'écran OLED
void SSD1306_init(void);

// Efface tout l'écran et remet le curseur à 0,0
void SSD1306_clear(void);

// Positionne le curseur (x: 0-127, y: 0-7 pour les pages)
void SSD1306_setCursor(unsigned char x, unsigned char y);

// Affiche une chaîne de caractères (gère \n et le retour à la ligne)
void SSD1306_print(const char* text);

// Affiche un caractère unique via la table font8x8
void SSD1306_writeChar(char c);

// Envoie une commande brute à l'écran
void SSD1306_sendCommand(unsigned char cmd);

#endif
