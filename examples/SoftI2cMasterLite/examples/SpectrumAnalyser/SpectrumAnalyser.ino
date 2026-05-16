/* Audio Spectrum Analyzer ASA2605V0
 * Ardui89 Mini Board (STC15W408AS-DIP16 / 29.4912MHz)
 * Cyril BARBATO 2026
 */

//#define SDA P1_4  // To redefine if différent from lib Ardui89 by défaut
//#define SCL P1_5  // To redefine if différent from lib Ardui89 by défaut

#include "SoftI2cMasterLite.h"
#include "SoftSSD1306Lite.h"
#include "fix_fft.h"

// replace sqrt by sqrt 8 bits
#define sqrt sqrt8

// ============================================================
// --- DESSIN D'UNE BARRE VERTICALE SUR L'OLED ---
// x   : colonne de départ (0..127)
// h   : hauteur en pixels (0..48)
// ============================================================

void OLED_DrawMSBar(unsigned char x, unsigned char h) {
    unsigned char page, p_bits;
    h++;
    if (h > 48) h = 48;

    for (page = 0; page < 6; page++) {
        SSD1306_setCursor(x, 5 - page);

        if (h >= 8) {
            p_bits = 0xFF;
            h -= 8;
        } else if (h > 0) {
            p_bits = (0xFF << (8 - h));
            h = 0;
        } else {
            p_bits = 0x00;
        }

        // Supprime le pixel du bas sur la première page (ligne de fond)
        if (page == 0) {
            p_bits &= 0x7F;
        }

        SoftI2cMaster_start(0x78);
        SoftI2cMaster_write(0x40);
        for (unsigned char w = 0; w < 12; w++) {
            SoftI2cMaster_write(p_bits);
        }
        SoftI2cMaster_stop();
    }
}

// ============================================================
// --- DONNÉES FFT ---
// ============================================================
__xdata char data[128];
__xdata char im[128];

// Indices FFT correspondant aux 7 bandes (63Hz → 16kHz)
PROGMEM unsigned char msgeq7_bins[] = { 1, 2, 5, 8, 16, 32, 50 };

// Labels affichés sous chaque barre
PROGMEM const char* labels[] = { "63", "160", "400", "1K", "2K5", "6K", "16K" };

// ============================================================
// --- SETUP ---
// ============================================================
void setup() {

#if defined(ARDUINO_ARCH_8051)
    Serial89Init();
#endif
    Serial.begin(9600);
    while (!Serial) { ; }
    
    // --- OLED ---
    SSD1306_init();
    SSD1306_clear();

    // Affiche les labels de fréquence en bas (page 6 = dernière ligne)
    SSD1306_setCursor(0, 6);
    for (unsigned char i = 0; i < 7; i++) {
        SSD1306_print(labels[i]);
    }

    // Dessin de barres de test au démarrage
    for (unsigned char i = 0; i < 7; i++) {
        OLED_DrawMSBar(i * 18, (i + 1) * 6);
    }

    //Init ADC -> A0
    analogPin(A0); // or pinMode(A0, INPUT_ANALOG);

    Serial.println("Ready>");
}

// ============================================================
// --- LOOP ---
// ============================================================
void loop() {
    long sum = 0;
    unsigned int val=0;
    unsigned int min_val = 1024;
    unsigned int max_val = 0;

    // 1. Acquisition et détection d'amplitude réelle
    for (unsigned char i = 0; i < 128; i++) {
        val = analogRead(0);
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
        
        data[i] = (char)(val >> 2); 
        im[i] = 0;
        sum += (unsigned char)data[i];
    }

    // 2. Calcul du centre
    char centre = (char)(sum / 128);
    
    // 3. SEUIL DE SÉCURITÉ (Gate)
    // Si la différence entre le point le plus haut et le plus bas est < 4
    // ou si on est en saturation (0 ou 1020), on éteint tout.
    if ((max_val - min_val) < 4 || val < 10 || val > 1010) {
        for (unsigned char b = 0; b < 7; b++) {
            OLED_DrawMSBar(b * 18, 0);
        }
        Serial.println("SILENCE (ADC=%d)", val);
    } 
    else {
        // 4. On traite le signal car il bouge !
        for (unsigned char i = 0; i < 128; i++) {
            data[i] -= centre;
        }

        fix_fft(data, im, 7, 0);

        for (unsigned char b = 0; b < 7; b++) {
            int r = data[msgeq7_bins[b]];
            int i = im[msgeq7_bins[b]];
            unsigned int mag = sqrt((unsigned int)(r * r + i * i));
            
            unsigned char h = 0;
            if (mag > 2) h = (mag - 2) * 3; // Gain x3
            if (h > 47) h = 47;
            OLED_DrawMSBar(b * 18, h);
        }
        Serial.println("DATA (ADC=%d)", val);
    }
    
    delay(1);
}
