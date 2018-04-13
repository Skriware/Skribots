#include <Skribot.h>
/*
 * In this example we present the most basic algorithm for line followe with one sensor only. Robot will search for the line by turning Right if it sees the line and turning left if it don't.
 * 
 * Connections for robot:
 * 
 * Line sensor plugged to L1 slot on Skriware EDU shield.
 * Two rotors plugged by Skriware EDU Shield, LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * IMPORTANT!!!
 * Timmings for turns are set for example values, when building own robot you should do some tests to set good working turning times.
 */
Skribot robot;
                        
void setup() {
  robot.AddLineSensor("L1");         //Adding line sensor on slot L1 of Skriware EDU shield
  robot.AddDCRotor("LEFT");        //adding rotors for movement
  robot.AddDCRotor("RIGHT");
  robot.SetSpeed(250);
}

void loop() {
  if(robot.ReadLineSensor("L1")){           	//Chcecking if sensor is detecting the line below it. It returns 1( there is a line below) or 0 (there is no line);
    
    robot.TurnLeft(200);                		// Turning Left
                      
  }else{
    
    robot.TurnRight(200);               		//Turning Right  
  }

}
