#include "DistSensor.h"

DistSensor::DistSensor(int EP,int Trigg, String Name){
  EchoPin = EP;
  TriggerPin = Trigg;
  name = Name;
   pinMode(Trigg, OUTPUT);
   pinMode(EP, INPUT);
}

DistSensor::DistSensor(int EP,int Trigg, byte _ID){
  EchoPin = EP;
  TriggerPin = Trigg;
  ID = _ID;
   pinMode(Trigg, OUTPUT);
   pinMode(EP, INPUT);
}

  int DistSensor::ReadSensor(int cm){
    digitalWrite(TriggerPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin,LOW);
    unsigned long int sigT = pulseIn(EchoPin,HIGH,15000);
    long int l = sigT/58;
    if(l < cm && l > 0){
      return(l);
    }
    else{
      return(cm);
    }

  }

  int DistSensor::RawReadSensor(){
    digitalWrite(TriggerPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin,LOW);
    unsigned long int sigT = pulseIn(EchoPin,HIGH,15000);
    long int l = sigT/58;
    return(l);
  }

  String DistSensor::GetName(){
    return(name);
  }

  byte DistSensor::GetID(){
    return(ID);
  }