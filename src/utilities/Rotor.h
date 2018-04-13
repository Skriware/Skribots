#ifndef Rotor_H
#define Rotor_H
#include "Arduino.h"
  class Rotor
 {
  public:
  	Rotor(int SpeedPin,int DirectionPin);
    void SetSpeed(int speed);
    void SetDirection(int dir);
    void Move();
    void Stop();
    int GetSpeed();
    int GetDirection();
  private:
  #ifndef _VARIANT_BBC_MICROBIT_
  byte _speed_pin;
  byte _dir_pin;
  #else
  byte _dir_pin_1;
  byte _dir_pin_2;
  #endif
  int _speed;
  int _dir;
 };

 #endif