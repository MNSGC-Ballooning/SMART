#include "Smart.h"

Smart::Smart(byte pin):
  servoPin(pin) {
}

void Smart::initialize() {
  servo.attach(servoPin);
  servo.write(170);
}

void Smart::release() {
  servo.write(0);
}