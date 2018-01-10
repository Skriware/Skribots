#include <SkriBot.h>
/*
 * In this example we present Line folower which uses three sensors from the LineSenosor bar. 
 * We can read specific values for each of 3 detectors in Line detector left, right and center instead of reading from it as one. 
 * 
 * Algorithm is explained in comments below.
 * 
 * Connections for robot:
 * 
 * Line sensor plugged to L1 slot on Skriware EDU shield -this sensor needs to be placed on the left side of the robot.
 * Line sensor plugged to L2 slot on Skriware EDU shield -this sensor needs to be placed on the right side of the robot. 
 * Line sensor plugged to L3 slot on Skriware EDU shield -this sensor needs to be placed on the center of the robot
 * Two rotors plugged by Skriware EDU Shield, LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * IMPORTANT!!!
 * Timmings for turns are set for example values, when building own robot you should do some tests to set good working turning times.
 */

SkriBot robot;
bool LeftSensor;
bool RightSensor;
bool CenterSensor;                    // variables to keep sensor measurements.
void setup() {
  robot.AddLineSensor("L1");          //Adding line sensor
  robot.AddLineSensor("L2"); 
  robot.AddLineSensor("L3");      
  
  robot.AddDCRotor("LEFT");           //adding rotors for movement
  robot.AddDCRotor("RIGHT");
  robot.SetSpeed(250);

}

void loop() {

LeftSensor 		= robot.ReadLineSensor("L1");
CenterSensor 	= robot.ReadLineSensor("L2");
RightSensor		= robot.ReadLineSensor("L3");				// Reading from line sensors
	
if(!LeftSensor && !RightSensor && CenterSensor){                                  //if we see line on the middle sensor we can proceed forward
    robot.MoveForward();
}else if(LeftSensor){                                                             // Line is on the Left we want to have it in the middle - let's turn Right 
    robot.FaceLeft(150);                                                         
}else if(RightSensor){                                                            // Line is on the Right we want to have it in the middle - let's turn Left
    robot.FaceRight(150);                                                     
}else if(CenterSensor && RightSensor){                                            //Sharp Right turn
    robot.FaceRight(300);
}else if(LeftSensor && CenterSensor){                                             //Sharp Left  turn
    robot.FaceLeft(300);
}
else{
  	robot.FaceRight(100);
}

    
    
}
