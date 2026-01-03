#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);


void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(115200);
  Serial.println("Hello World!");
  Serial.printf("Result of myFunction: %d\n", result);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Turn on LED...");
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  Serial.println("Turn off LED...");
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}