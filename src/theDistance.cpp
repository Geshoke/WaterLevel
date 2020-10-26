#include <Arduino.h>
#include "theDistance.h"
#include <RunningMedian.h>

// const int trigPin = 9;
// const int echoPin = 10;
int distance;
long duration;

int HCSR04measure(int trigPin, int echoPin) {
  // int val = 0;
  
  RunningMedian twenty = RunningMedian(20);//array for twenty values created here

  for (int i = 0; i < 20; i++) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    // val += distance;  //val=val+distance
    delay(100);
    twenty.add(distance);
  }
  //distance = val / 20;
  float median = twenty.getMedian();
  Serial.print("Distance: ");
  Serial.println(distance);
  return median;
}