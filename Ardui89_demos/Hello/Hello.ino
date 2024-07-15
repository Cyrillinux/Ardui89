/*
 * Hello
 */

// the setup function runs once when you press reset or power the board
void setup() {
  // Serial port init
  // Serial89Init(); // Serial 89 init not necessary since V.0.1.0
  Serial.begin(9600); // Monitor init (F_CPU = 11.0592Mhz)
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Hello the world !");
  delay(1000);                       // wait for a second
}
