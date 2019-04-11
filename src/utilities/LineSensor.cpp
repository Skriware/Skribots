#include "LineSensor.h"

LineSensor::LineSensor(int PinL, String Name){
 name = Name;
 sensorPin = PinL;
  logicBorder = DEFAULT_LINE_SENSOR_LOGIC_BORDER;
    
}

LineSensor::LineSensor(int PinL, int _id){
 id = _id;
 sensorPin = PinL;
 name = "";
  logicBorder = DEFAULT_LINE_SENSOR_LOGIC_BORDER;
}

int LineSensor::ReadSensor(){
  int readout = analogRead(sensorPin);
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

int LineSensor::GetSensorPin(){
    return(sensorPin);
}

void LineSensor::SetLogicBorder(int border){
  logicBorder = border;
}

String LineSensor::GetName(){
  return(name);
}

