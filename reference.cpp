#include <SoftwareSerial.h>
#include <Arduino.h>


// defines hcSR04 pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
int led = 6;
long duration;
int distance;
String apiKey = "CO8J6D0RYD3BPK28";
SoftwareSerial ser(7, 8); // RX, TX

// this runs once
void setup() {
  ser.begin(9600);
  Serial.begin(9600);
  ser.println("AT+CIPSHUT\r\n");
  Serial.print("code begining");
 // pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  delay(100);
}

// the loop
void loop() {
  for (int i = 0; i< 5; i++){
  float measured;
  measured = HCSR04measure();

  char buf[16];
  String strMeasrd = dtostrf(measured, 2, 0, buf);
  //Serial.println(strMeasrd);


  String input = "";


  // TCP connection
  ser.println("AT+CIPSHUT\r\n");
  delay(2000);
  ser.write("AT\r\n");


  delay(2000);
  ser.write("AT+CIPMUX=0\r\n");
  delay(2000);
  ser.write("AT+CSTT=“safaricom”,“saf”,“data”\r\n");
  delay(2000);
  ser.write("AT+CIICR\r\n");
  delay(3000);
  ser.write("AT+CIFSR\r\n");
  delay(3000);

  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",\"80\"";
  ser.println(cmd);
  // ser.write("\r\n");
  delay(2000);
  Serial.println(cmd);


  // prepare GET string
  String getStr;
  getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr += "&field1=";
  getStr += String(strMeasrd);
  getStr += "\r\n\r\n";


  // send data length
  String cmd2 = "AT+CIPSEND=";
  cmd2 += String(getStr.length() + 2);
  ser.println(cmd2);
  delay(2000);
  Serial.println(cmd2);
  ser.println(getStr);
  delay(5000);
  Serial.println(getStr);
  delay(500);
  ser.println("AT+CIPSHUT\r\n");
  
  }



  delay(120000);//SET THE DELAY TIME. CURRENT IS 2 MINUTES
}

//THIS IS THE METHOD THAT THE ULTRASONIC SENSOR IS WORKING ON.
//CALLED IN THE VOID LOOP
int HCSR04measure() {
  int val = 0;
  for (int i = 0; i < 10; i++) {
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
    val += distance;  //val=val+distance
    delay(500);
  }
  distance = val / 10;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}
