#include <SkriBot.h>
/*
 * In this example we present basic algorithm for line followe with two line sensors. Robot will go forward if both don't see the line and lurn if one will. 
 * We want our robot to keep line between sensors.
 * 
 * Connections for robot:
 * 
 * Line sensor plugged to L1 slot on Skriware EDU shield -this sensor needs to be placed on the left side of the robot.
 * Line sensor plugged to L2 slot on Skriware EDU shield -this sensor needs to be placed on the right side of the robot. 
 * Two rotors plugged by Skriware EDU Shield, LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * IMPORTANT!!!
 * Timmings for turns are set for example values, when building own robot you should do some tests to set good working turning times.
 */
SkriBot robot;
bool LEFTSens, RIGHTSens;                 // variables to keep sensor measurements.
                        
void setup() {
  robot.AddLineSensor("L1");         //Adding line sensor
  robot.AddLineSensor("L2");       
  
  robot.AddDCRotor("LEFT");        //adding rotors for movement
  robot.AddDCRotor("RIGHT");
  robot.SetSpeed(250);
}

void loop() {
  LEFTSens   = robot.ReadLineSensor("L1");   //Reading from first sensor
  RIGHTSens  = robot.ReadLineSensor("L2");
  
  if(!LEFTSens && !RIGHTSens){           //Chcecking if both sensor are detecting the line below it.
    
    robot.MoveForward();                 // Going Forward
                      
  }else if(LEFTSens){                                 
    
    robot.TurnLeft(200);                 //Turning Left 
    
  }else if(RIGHTSens){                   //Reading from second sensor
    
    robot.TurnRight(200);                //Turning Right
  }

}
