#include<Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_
#include "RobotLED.h"

	RobotLED::RobotLED(int pin,String _name,byte N_LED){
		pixel = new Adafruit_NeoPixel(N_LED, pin, NEO_GRB + NEO_KHZ800);
        name = _name;
        nLED = N_LED;
        id = 99;
        pixel->begin();
	}

    RobotLED::RobotLED(int pin,byte _id,byte N_LED){
        pixel = new Adafruit_NeoPixel(N_LED, pin, NEO_GRB + NEO_KHZ800);
        id = _id;
        nLED = N_LED;
        name = "none";
        pixel->begin();
    }

    void RobotLED::turnON(int R, int G, int B,byte N_LED){

          if(N_LED == 0){
            for(int yy = 0; yy < nLED; yy++)pixel->setPixelColor(yy, pixel->Color(R,G,B));
          }else{ 
          pixel->setPixelColor(N_LED-1, pixel->Color(R,G,B)); 
          }
          pixel->show(); 
          delay(10);
    }

    void RobotLED::turnOFF(byte N_LED){
            if(N_LED == 0){
                for(int yy = 0; yy < nLED; yy++)pixel->setPixelColor(yy, pixel->Color(0,0,0));
            }else{
            pixel->setPixelColor(0, pixel->Color(0,0,0)); 
            }
            pixel->show(); 
            delay(10);

             if(N_LED == 0){
                for(int yy = 0; yy < nLED; yy++)pixel->setPixelColor(yy, pixel->Color(0,0,0));
            }else{
            pixel->setPixelColor(0, pixel->Color(0,0,0)); 
            }
            pixel->show(); 
            delay(10);                              //do the cycle again to ensure that there was no buffer clerance problem
    }


    void RobotLED::Set_Predef_Color(int color_id,byte N_LED){          //Not used so far
        switch(color_id){
            case 0 : 
                turnON(0,0,255,N_LED);
            break;
             case 1 : 
                turnON(0,255,0,N_LED);
            break;
             case 2 : 
                turnON(255,0,0,N_LED);
            break;
             case 3 : 
                turnON(255,255,255,N_LED);
            break;
             case 4 : 
                turnON(0,255,255,N_LED);
            break;
             case 5 : 
                turnON(255,0,255,N_LED);
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

    #endif