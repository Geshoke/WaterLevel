#include <Arduino.h>
#include "theDistance.h"
#include <SoftwareSerial.h>
#include <Http.h>
#include <Sim800.h>
#include <thePostRequest.h>


//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

const int trigPin = 9;
const int echoPin = 10;

////////////////////////////////////////////////
// unsigned int RX_PIN = 2;
// unsigned int TX_PIN = 3;
// unsigned int RST_PIN = 12;
// const char BEARER[] PROGMEM = "internet";

// bool theVal;
///////////////////////////////////////////////


void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read()); //Forward what Software Serial received to Serial Port
  }
}

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  // Serial.print("code begining");
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  delay(100);

  SIM800 wakeUp();
  Serial.println("working");

  // PostRequest(WaterDepth);

  int WaterDepth = HCSR04measure(trigPin, echoPin);
  PostRequest(WaterDepth);

}

void loop()
{
  // int WaterDepth = HCSR04measure(trigPin, echoPin);

  // PostRequest(WaterDepth);
  // delay(10000);

  // put your main code here, to run repeatedly:

  // updateSerial();
}
