#include "Smart.h"

Smart::Smart(byte pin, unsigned long cutAlt, unsigned long cutTime):
  servoPin(pin), cutAlt(cutAlt), cutTime(cutTime) {
}

void Smart::initialize() {
  servo.attach(servoPin);
  servo.write(170);
}

void Smart::release() {
  for (byte i = servo.read(); i > 0; i--) {
    servo.write(i);
    delay(20);
  }
}