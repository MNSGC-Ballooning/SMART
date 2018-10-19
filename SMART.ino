#include "src\Smart.h"
#include <Relay_XBee.h>

#define smartPin 5
#define radioLED_pin 7

//Parameters
float cutTime = 80;
float Timer=1;
bool released = false;
int smartUnit = 1; //Change the number depending on the external SMART unit being used;


//SoftwareSerial xBee_Serial = SoftwareSerial(2,3);
#define xBee_Serial Serial
const String ID = "SMART";

Smart smart = Smart(smartPin);

void setup() {
  smart.initialize();
  //gps.initialize();
  xBeeSetup();
}

void loop() {
  //gps.update();
  if (!released && (millis()/60000.0 > cutTime)) {
    smart.release();
    
    released = true;
  }
  xBeeCommand();
  
  if (millis()/60000.0>Timer)
  {Timer=Timer+1;
  float TRemain = cutTime-millis()/60000.0;
  String Remain="Auto: Time remaining is " + String(TRemain) + "minutes.";
  beacon(Remain);
  }
  SpamControl();
  
}
