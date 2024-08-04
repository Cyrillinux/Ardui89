/*
 * Hello
 */

// the setup function runs once when you press reset or power the board
void setup() {
// Serial port init
#if defined(ARDUINO_ARCH_8051)
  Serial89Init(); // Serial 89 init
#endif
  Serial.begin(9600); // Monitor init (F_CPU = 11.0592Mhz)
  while (!Serial) { ; } // Wait if Serial is not init
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Hello the world !");
  delay(1000);                       // wait for a second
}
