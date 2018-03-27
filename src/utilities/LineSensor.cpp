#include "LineSensor.h"


LineSensor::LineSensor(int PinL, String Name){
 name = Name;
 sensorPin = PinL;
  delay(500);
  int blackReadOut = 0;
  /*for(int kk = 0; kk< 100; kk++){
    blackReadOut += analogRead(sensorPin);
    delay(20);
  }*/
    blackReadOut = blackReadOut/100;
    logicBorder = 500;
    //Serial.println(logicBorder);
}

LineSensor::LineSensor(int PinL, int _id){
 id = _id;
 sensorPin = PinL;
 name = "";
  delay(500);
  int blackReadOut = 0;
    blackReadOut = blackReadOut/100;
    logicBorder = 500;
}

int LineSensor::ReadSensor(){
  int readout = analogRead(sensorPin);
  Serial.print("READ:");
  Serial.println(readout);
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

