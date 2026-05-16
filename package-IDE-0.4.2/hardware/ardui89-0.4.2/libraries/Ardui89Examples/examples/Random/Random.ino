long randNumber;

void setup() {

   // Serial port init
#if defined(ARDUINO_ARCH_8051)
  Serial89Init(); // Serial 89 init
#endif
  Serial.begin(9600);
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(12345);
}

void loop() {
  // print a random number from 0 to 299
  randNumber = random(300);
  Serial.println("%d\n", randNumber);

  // print a random number from 10 to 19
  randNumber = random(10, 20);
  Serial.println("%d\n", randNumber);

  delay(50);
}
