#include "SoftI2cMasterUni.h"
#include "SoftSSD1306Uni.h"

SoftI2cMaster i2cWire;
SSD1306 display;

void setup() {

    pinMode(A2, OUTPUT);digitalWrite(A2, LOW); // GND
    pinMode(A3, OUTPUT);digitalWrite(A3, HIGH); //VCC

    SoftI2cMaster_init(&i2cWire, A5, A4); // SCL sur GPIO A5, SDA sur GPIO A4
    SSD1306_init(&display, &i2cWire);

    display.println("\nWAIT...");
    display.clear();
    display.println("*BONJOUR !>");
    display.clear();
    display.print("TEST:");
    display.println("L1");
    display.println("L2");
}

void loop() {
    // Rien ici pour le moment
}
