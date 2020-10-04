#include <Arduino.h>
#include "theDistance.h"

void setup() {
  Serial.begin(9600);
  Serial.print("code begining");
   pinMode(9, OUTPUT); // Sets the trigPin as an Output
  pinMode(10, INPUT); // Sets the echoPin as an Input
  delay(100);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
 HCSR04measure();
  
}