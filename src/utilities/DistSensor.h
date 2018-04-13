#ifndef DistSensor_H
#define DistSensor_H
#include "Arduino.h"

  class DistSensor
 {
  public:
    DistSensor(int EP,int Trigg, String Name);
    DistSensor(int EP,int Trigg, byte id);
    int ReadSensor(int cm);
    int RawReadSensor();
    String GetName();
    byte GetID();
  private:
  byte EchoPin;
  byte TriggerPin;
  String name;
  byte ID;
  
 };
 #endif
