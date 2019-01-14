#include "src\Smart.h"
#include <Relay_XBee.h>

#define smartPin 5
#define radioLED_pin 7

//Parameters
//float cutTime = 80;
float Timer=1;
bool released = false;
int smartUnit = 1; //Change the number depending on the external SMART unit being used;


//SoftwareSerial xBee_Serial = SoftwareSerial(2,3);
#define xBee_Serial Serial
const String ID = "SMART";
float prevTime = 0;

Smart smart = Smart(smartPin);

void setup() {
  smart.initialize();
  //gps.initialize();
  xBeeSetup();
}

void loop() {
  xBeeCommand();
  SpamControl();
  beacon(ID + String(smartUnit) + "-" + statuS()); 
}
