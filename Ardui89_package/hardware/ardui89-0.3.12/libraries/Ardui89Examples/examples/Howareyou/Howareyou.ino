/*
 * How Are You ?
 * 2024-2025 (c) Cyril BARBATO
 */

// Setup fonction
void setup()
{
  // Serial port init
#if defined(ARDUINO_ARCH_8051)
  Serial89Init(); // Serial 89 init
#endif
  Serial.begin(9600); // Monitor init (F_CPU = 11.0592Mhz)
  // Starting Message
  Serial.println("Starting...");
  // First question message
  Serial.println("Ready. How are you ? Fine ?");
 }
// Main loop
void loop()
{ 
  // Info from serial port available ?
  if (Serial.available()>0) {
    // Read char info from serial port
    char c = Serial.read();
    // Print result
    Serial.println("%c", c);
    delay(1000);
    // New question message
    Serial.println("How are you ? Fine ?");
  }
}
