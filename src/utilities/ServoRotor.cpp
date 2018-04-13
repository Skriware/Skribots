#include <Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_
#include "ServoRotor.h"

ServoRotor::ServoRotor(int Pin, String Side, int neu){
  _pin  = Pin;
  _side = Side; 
  servo.attach(_pin,1000,2000);
  _neutral = neu;
  servo.writeMicroseconds(_neutral);
}

void ServoRotor::Move(char dir){
  switch(dir){
    case 'F':
      servo.writeMicroseconds(_neutral + 400);
    break;
    case 'B':
      servo.writeMicroseconds(_neutral - 400);
    break;
  }
}

void ServoRotor::Stop(int serv){
  servo.writeMicroseconds(_neutral);
}
#endif