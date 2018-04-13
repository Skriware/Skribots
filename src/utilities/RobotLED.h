#ifndef RobotLED_H
#define RobotLED_H
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

  class RobotLED
 {
  public:
  	RobotLED(int pin,String name);
  	RobotLED(int pin,byte id);
    void turnON(int R,int G, int B);
    void Set_Predef_Color(int color_id);
    void turnOFF();
    byte GetID();
    String GetName();
  	
  private:
 Adafruit_NeoPixel pixel;
 byte id;
 String name;
 };

 #endif