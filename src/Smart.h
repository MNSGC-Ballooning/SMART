#ifndef Smart_h
#define Smart_h

#include <Arduino.h>
#include <Servo.h>

class Smart {
  public:
    Smart(byte pin, unsigned long cutAlt, unsigned long cutTime);
    void initialize();
    void release();
  private:
    byte servoPin;
    unsigned long cutAlt, cutTime;
    Servo servo;
};

#endif