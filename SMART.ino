#include "src/Smart.h"
#include <Relay_XBee.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define smartPin 5
#define radioLED_pin 7
#define ONE_WIRE_BUS 2 //EXT Smart Temp 1
#define TWO_WIRE_BUS 4 //EXT Smart Temp 2

//Dallas Temperature Sensors
OneWire oneWire1(ONE_WIRE_BUS);
OneWire oneWire2(TWO_WIRE_BUS);
DallasTemperature sensor1(&oneWire1);
DallasTemperature sensor2(&oneWire2);
float t1;
float t2;

float cutTime = 80;
float Timer=1;
bool released = false;

SoftwareSerial xBee_Serial = SoftwareSerial(2,3);
//#define xBee_Serial Serial
const String ID = "SMART";

Smart smart = Smart(smartPin);

void setup() {
  smart.initialize();
  //gps.initialize();
  xBeeSetup();
//Initiate Temp Sensors
  sensor1.begin();
  sensor2.begin();
}

void loop() {
  //gps.update();
  if (!released && (millis()/60000.0 > cutTime)) {
    smart.release();
    
    released = true;
    sensor1.requestTemperatures();
    sensor2.requestTemperatures();
    t1 = sensor1.getTempCByIndex(0) + 273.15;
    t2 = sensor2.getTempCByIndex(0) + 273.15;
  }
  xBeeCommand();
  
  if (millis()/60000.0>Timer)
  {Timer=Timer+1;
  float TRemain = cutTime-millis()/60000.0;
  String Remain="Time remaining is " + String(TRemain) + "minutes." + "\n";
  beacon(Remain);
  }
  String Temp1="Temperature of EXT Smart 1 is " + String(t1) + "\n";
  String Temp2="Temperature of EXT Smart 2 is " + String(t2) + "\n";
  beacon(Temp1);
  beacon(Temp2);
  Serial.print(Temp1);
  Serial.print(Temp1);
}
