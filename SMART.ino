#include "src\Smart.h"
#include <CopernicusGPS.h>

#define smartPin 11
#define cutTime 70 //Time in minutes

SoftwareSerial ss = SoftwareSerial(2,3);
CopernicusGPS gps = CopernicusGPS(&ss);

Smart smart = Smart(smartPin);

void setup() {
  smart.initialize();
  gps.initialize();
}

void loop() {
  gps.update();
  if (millis()/60000 > cutTime)
    smart.release();
}
