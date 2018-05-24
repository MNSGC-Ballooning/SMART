#include "src\Smart.h"
//#include <CopernicusGPS.h>

#define smartPin 10
#define cutTime 70 //Time in minutes
#define light 9
#define onlightn 7
#define onlightp 6

bool released = false;

//SoftwareSerial ss = SoftwareSerial(2,3);
//CopernicusGPS gps = CopernicusGPS(&ss);

Smart smart = Smart(smartPin);

void setup() {
  smart.initialize();
  //gps.initialize();
  pinMode(light, OUTPUT);
  pinMode(onlightn, OUTPUT);
  pinMode(onlightp, OUTPUT);
  Serial.begin(115200);
  Serial.println("Testing");
  digitalWrite(onlightn, LOW);
  digitalWrite(onlightp, HIGH);
}

void loop() {
  //gps.update();
  if (!released && (millis()/60000.0 > cutTime-.2)){
    digitalWrite(light, HIGH);}
  if (!released && (millis()/60000.0 > cutTime)) {
    Serial.print("Releasing");
    smart.release();
    
    released = true;
  }
  delay(5000);
  digitalWrite(light, LOW);
}
