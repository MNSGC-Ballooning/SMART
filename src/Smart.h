#ifndef Smart_h
#define Smart_h

#include <Arduino.h>
#include <Servo.h>

class Smart {
  public:
    Smart(byte pin);
    void initialize();
    void release();
  private:
    byte servoPin;
    Servo servo;
};

#endif