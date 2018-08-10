#ifndef RobotLEDM_H
#define RobotLEDM_H
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "StatusLED.h"

class RGB_LED_Matrix
 {
  public:
  	RGB_LED_Matrix(int pin,byte _matrix_Rows, byte _matrix_Columns, String _name);
    void turnON(byte R,byte G,byte B);
    void pixelTurnOn(byte row_Id, byte column_Id,byte R,byte G,byte B);
    void turnOFF();
    void setByteConfiguration(uint8_t matrixConfiguration[8], color _color);
    byte GetID();
    String GetName();
  	
  private:
 Adafruit_NeoPixel pixels;
 byte id,matrix_Rows,matrix_Columns,nLeds;
 String name;
 };

#endif