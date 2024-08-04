/*
  Blink 2 LED (BLUE and RED) on D0 and D1 alternativly
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(0, OUTPUT); // BLUE LED
  pinMode(1, OUTPUT); // RED LED
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(0, HIGH);   // turn the BLUE LED on (HIGH is the voltage level)
  digitalWrite(1, LOW);    // turn the RED LED off by making the voltage LOW
  delay(150);              // wait for 150 milliseconds
  digitalWrite(0, LOW);    // turn the BLUE LED off by making the voltage LOW
  digitalWrite(1, HIGH);   // turn the RED LED on (HIGH is the voltage level)
  delay(150);              // wait for 150 milliseconds
}
