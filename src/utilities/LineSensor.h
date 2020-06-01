#ifndef LineSensor3_H
#define LineSensor3_H
#include "Arduino.h"
#ifdef ESP_H
#define DEFAULT_LINE_SENSOR_LINE_READ_OUT 2660
#define DEFAULT_LINE_SENSOR_NO_LINE_READ_OUT 1220
#else
#define DEFAULT_LINE_SENSOR_LINE_READ_OUT 400
#define DEFAULT_LINE_SENSOR_NO_LINE_READ_OUT 0
#endif
  class LineSensor
 {
  public:
    LineSensor(int InputPin,String name);
    LineSensor(int InputPin,int id);;
    int ReadSensorRaw();
    int ReadSensorScaled();
    int ReadSensor();
    void SetLogicBorder(int lb=0);
    String GetName();
    int GetID();
    int GetSensorPin();
    void Line_Readout();
    void No_Line_Readout();
    int GetLogicBorder();
  private:
    int id;
    int Line_Read;
    int No_Line_Read;
  	int logicBorder;
  	int sensorPin;  //sensor read out is from 0 to 1000 where 0 is minimum reflectance(line) and 1000 is maximum reflectance(no line) need to be set for some value to recognise line under sensor
    String name; 
 };

 #endif
