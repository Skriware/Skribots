#include <Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_
#include "RGB_LED_Matrix.h"

  	RGB_LED_Matrix::RGB_LED_Matrix(int pin,byte _matrix_Rows, byte _matrix_Columns, String _name){
        nLeds = _matrix_Columns*_matrix_Rows;
        matrix_Rows = _matrix_Rows;
        matrix_Columns = _matrix_Columns;
        pixels = Adafruit_NeoPixel(nLeds, pin, NEO_GRB + NEO_KHZ800);
        pixels.begin();
        name = _name;

    }
    void RGB_LED_Matrix::turnON(byte R,byte G,byte B){

      for(int yy = 0; yy < nLeds; yy++) pixels.setPixelColor(yy, pixels.Color(R,G,B)); 
          pixels.show(); 
          delay(10);

    }
    void RGB_LED_Matrix::pixelTurnOn(byte row_Id, byte column_Id,byte R,byte G,byte B){
      int LedId = (row_Id - 1) * matrix_Columns + column_Id-1; 
      pixels.setPixelColor(LedId, pixels.Color(R,G,B)); 
      pixels.show(); 
      delay(10);
    }
    void RGB_LED_Matrix::turnOFF(){
       for(int yy = 0; yy < nLeds; yy++) pixels.setPixelColor(yy, pixels.Color(0,0,0)); 
          pixels.show(); 
          delay(10);
    }
    void RGB_LED_Matrix::setByteConfiguration(uint8_t matrixConfiguration[8], color _color){

      byte R,G,B;

      switch (_color){
        case RED:
          R = 255;
          G = 0;
          B = 0;
        break;
        case GREEN:
          R = 0;
          G = 255;
          B = 0;
        break;
        case BLUE:
          R = 0;
          G = 0;
          B = 255;
        break;
        case YELLOW:
          R = 255;
          G = 255;
          B = 0;        
        break;
        case PURPLE:
          R = 255;
          G = 0;
          B = 255;
        break;
        case WHITE:
          R = 255;
          G = 255;
          B = 255;
        break;
      }
    byte tmpR,tmpG,tmpB;
    int LedId;
    for(int yy = 1; yy < 9 ; yy++){
      Serial.println();
        for(int zz = 0; zz < 8 ; zz ++){
          Serial.print((bool)(matrixConfiguration[yy-1] & (1 << zz)));
          if(matrixConfiguration[yy-1] & (1 << zz)){
            tmpR = R;
            tmpB = B;
            tmpG = G;
          }else{
            tmpR = 0;
            tmpG = 0;
            tmpB = 0;
           
          }
      LedId = (yy - 1) * matrix_Rows + zz; 
      pixels.setPixelColor(LedId, pixels.Color(tmpR,tmpG,tmpB)); 
        }
    }
    pixels.show(); 
    delay(10);
    }
    byte RGB_LED_Matrix::GetID(){
      return id;

    }
    String RGB_LED_Matrix::GetName(){
      return name;
    }
  	

#endif