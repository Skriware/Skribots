#include "LineSensor.h"

LineSensor::LineSensor(int PinL, String Name){
 name = Name;
 sensorPin = PinL;
  delay(100);
  #ifndef ESP_H
    logicBorder = 400;
  #else
    logicBorder = 200;
  #endif
    
}

LineSensor::LineSensor(int PinL, int _id){
 id = _id;
 sensorPin = PinL;
 name = "";
#ifndef ESP_H
    logicBorder = 400;
  #else
    logicBorder = 200;
  #endif
}

int LineSensor::ReadSensor(){
  int readout = analogRead(sensorPin);
  #ifdef DEBUG_MODE
  Serial.print("READ:");
  Serial.println(readout);
  #endif
    if(readout > logicBorder){
      return(1);
    }else{
      return(0);
    }  
}

int LineSensor::ReadSensorRaw(){
    return(analogRead(sensorPin));
}

int LineSensor::GetID(){
    return(id);
}

void LineSensor::SetLogicBorder(int border){
  logicBorder = border;
}

String LineSensor::GetName(){
  return(name);
}

