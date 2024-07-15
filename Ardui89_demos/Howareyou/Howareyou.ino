/*
 * How Are You ?
 */

// Setup fonction
void setup()
{
  // Serial port init
  // Serial89Init(); // Serial 89 init not necessary since V.0.1.0
  Serial.begin(9600); // Monitor init (F_CPU = 11.0592Mhz)
  // Starting Message
  Serial.println("Starting...");
  // First question message
  Serial.println("How are you ? Fine ?");
 }
// Main loop
void loop()
{ 
  // Info from serial port available ?
  if (Serial.available()>0) {
    // Read char info from serial port
    char c = Serial.read();
    // Print result
    Serial.println("Ok : %c", c);
    delay(1000);
    // New question message
    Serial.println("How are you ? Fine ?");
  }
}
