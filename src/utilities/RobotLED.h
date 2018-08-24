#ifndef RobotLED_H
#define RobotLED_H
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

  class RobotLED
 {
  public:
  	RobotLED(int pin,String name, byte N_LED = 1);
  	RobotLED(int pin,byte id, byte N_LED = 1);
    void turnON(int R,int G, int B, byte LED_id  = 1);
    void Set_Predef_Color(int color_id, byte LED_id = 1);
    void turnOFF(byte LED_id = 1);
    byte GetID();
    String GetName();
  	
  private:
 Adafruit_NeoPixel *pixel;
 byte id,nLED;
 String name;
 };

 #endif