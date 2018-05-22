#include "src\Smart.h"
//#include <CopernicusGPS.h>

#define smartPin 10
#define cutTime .3 //Time in increments of 10 seconds

bool released = false;

//SoftwareSerial ss = SoftwareSerial(2,3);
//CopernicusGPS gps = CopernicusGPS(&ss);

Smart smart = Smart(smartPin);

void setup() {
  smart.initialize();
  //gps.initialize();
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
  delay(1000);
}
