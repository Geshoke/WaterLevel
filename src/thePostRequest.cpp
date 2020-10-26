#include <Arduino.h>
// #include "theDistance.h"
// #include <SoftwareSerial.h>
#include <Http.h>
#include <Sim800.h>
#include <thePostRequest.h>

//////////////////////////////////////
unsigned int RX_PIN = 2;
unsigned int TX_PIN = 3;
unsigned int RST_PIN = 12;
const char BEARER[] PROGMEM = "internet";

bool theVal;
////////////////////////////////////////

void PostRequest(int WaterDepth)
{
    //Build post string
    String TheString;
    TheString = "{\"date\":\"";
    TheString += WaterDepth;
    TheString += "\"}";

    Serial.println("the string");

    Serial.println(TheString);

    /////////////////////////////////////

    HTTP http(9600, RX_PIN, TX_PIN, RST_PIN);
    http.connect(BEARER);
    char response[256];
    // Result result = http.get("https://rujwascogis.site/gibro/waterlevel", response);
    http.post("134.122.48.46/gibro/waterlevel", TheString.c_str(), response);
    Serial.println(response);
    http.disconnect();
    int theSignal = http.readSignalStrength();
    Serial.println(theSignal);
    SIM800 sleep();

    //////////////////////////////////////////
}