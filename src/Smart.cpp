#include "Smart.h"

Smart::Smart(byte pin):
  servoPin(pin) {
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