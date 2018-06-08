#include "src\Smart.h"
#include <Relay_XBee.h>
//#include <CopernicusGPS.h>

#define smartPin 10
#define radioLED_pin 7
#define cutTime 70 //Time in minutes

bool released = false;

//SoftwareSerial ss = SoftwareSerial(2,3);
//CopernicusGPS gps = CopernicusGPS(&ss);

SoftwareSerial xBee_Serial = SoftwareSerial(2,3);
const String ID = "CMD";

Smart smart = Smart(smartPin);

void setup() {
  smart.initialize();
  //gps.initialize();
  xBeeSetup();
  Serial.begin(115200);
  Serial.println("Testing");
}

void loop() {
  //gps.update();
  if (!released && (millis()/60000.0 > cutTime)) {
    Serial.print("Releasing");
    smart.release();
    
    released = true;
  }
}
