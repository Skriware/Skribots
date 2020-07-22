#include "LineSensor.h"

LineSensor::LineSensor(int PinL, String Name){
 name = Name;
 sensorPin = PinL;
 Line_Read =  DEFAULT_LINE_SENSOR_LINE_READ_OUT;
 No_Line_Read =  DEFAULT_LINE_SENSOR_NO_LINE_READ_OUT;
 SetLogicBorder();
}

LineSensor::LineSensor(int PinL, int _id){
 id = _id;
 sensorPin = PinL;
 name = "";
 Line_Read =  DEFAULT_LINE_SENSOR_LINE_READ_OUT;
 No_Line_Read =  DEFAULT_LINE_SENSOR_NO_LINE_READ_OUT;
 SetLogicBorder();
}

int LineSensor::ReadSensor(){
  int readout = analogRead(sensorPin);
    if(readout < logicBorder){
      return(1);
    }else{
      return(0);
    }  
}
void LineSensor::Line_Readout(){
  int tmp=0;
  for(byte ii = 0; ii < 100; ii++){
    tmp+=analogRead(sensorPin);
    delay(10);
  }
  Line_Read = tmp/100;
  SetLogicBorder();
}
void LineSensor::No_Line_Readout(){
  int tmp=0;
  for(byte ii = 0; ii < 100; ii++){
    tmp+=analogRead(sensorPin);
    delay(10);
  }
  No_Line_Read = tmp/100;
  SetLogicBorder();
}

void LineSensor::SetLogicBorder(int lb){
  if(lb == 0){
    logicBorder = (No_Line_Read+ abs((Line_Read - No_Line_Read)/2));
  }else{
    logicBorder = lb;
  }
}

int LineSensor::ReadSensorRaw(){
    return(analogRead(sensorPin));
}

int  LineSensor::ReadSensorScaled(){
    return(100*analogRead(sensorPin)/4095);
}

int LineSensor::GetID(){
    return(id);
}

int LineSensor::GetSensorPin(){
    return(sensorPin);
}
String LineSensor::GetName(){
  return(name);
}

int LineSensor::GetLogicBorder(){
  return(logicBorder);
}

