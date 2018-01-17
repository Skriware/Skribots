#include "RobotLED.h"

	RobotLED::RobotLED(int pin,String _name){
		pixel = Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);
        name = _name;
        id = 99;
        pixel.begin();
	}

    RobotLED::RobotLED(int pin,byte _id){
        pixel = Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);
        id = _id;
        name = "none";
        pixel.begin();
    }

    void RobotLED::turnON(int R, int B, int G){
          pixel.setPixelColor(0, pixel.Color(R,G,B)); 
          pixel.show(); 
          delay(10);
    }

    void RobotLED::turnOFF(){
            pixel.setPixelColor(0, pixel.Color(0,0,0)); 
            pixel.show(); 
            delay(10);
    }


    void RobotLED::Set_Predef_Color(int color_id){

        switch(color_id){
            case 0 : 
                turnON(0,0,255);
            break;
             case 1 : 
                turnON(0,255,0);
            break;
             case 2 : 
                turnON(255,0,0);
            break;
             case 3 : 
                turnON(255,255,255);
            break;
             case 4 : 
                turnON(0,255,255);
            break;
             case 5 : 
                turnON(255,0,255);
            break;
            default:

            break;

        }
    }

    byte RobotLED::GetID(){
        return(id);
    }
    String RobotLED::GetName(){
    	return(name);
    }