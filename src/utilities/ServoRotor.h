#ifndef ServoRotor_H
#define ServoRotor_H
#include "Arduino.h"
#include "Servo.h"
  class ServoRotor
 {
  public:
  	ServoRotor(int Pin, String Side, int neutral = 1520);
    void Move(char Direction);
    void Stop(int S);
  private:
  int _pin;
  int _neutral;
  String _side;
  Servo servo;
 };

 #endif
