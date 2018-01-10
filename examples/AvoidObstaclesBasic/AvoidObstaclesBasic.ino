#include <SkriBot.h>
 /* In this example we present the simplest obstacle avoiding algorithm:
 * 
 * If you see obstacle on right side - Turn Left
 * If you see obstacle on left  side - Turn Right 
 * 
 * Connections for robot:
 * 
 * For this example robot has got two rotors plugged by Skriware EDU Shield, LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * Distance detectors needs two pins to be conected:
 * 
 * Detector on the Left Side of the robot: D1 slot on Skriware EDU Shield.
 * 
 * Detector on the Right Side of the robot: D2 slot on Skriware EDU Shield.
 *
 * WARNING!!!: You need to make tests to set optimal angle od distance detectors. 
 * Pointing them right ahead is not always the best option...
 *
 */
  SkriBot robot;                                  //defining our hero
  int LeftSensor,RightSensor;                     // variables to keep measurements form detectors 
void setup() {

  robot.AddDCRotor("LEFT");          //adding rotors for movement
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(250);               // set maximum speed
  
  robot.AddDistSensor("D1");         //adding Distance sensor on slots D1 and D2 on Skriware EDU shield
  robot.AddDistSensor("D2");

}

void loop() {
   LeftSensor = robot.ReadDistSensor("D1");       //Read distance to neares obstacle from both sensors distance. Obtained distance is in cm.
   RightSensor = robot.ReadDistSensor("D2");  

   if(LeftSensor > 20 && RightSensor > 20){       // There is no obstacles near both sensors -  move forward
      robot.MoveForward();
   }else if(LeftSensor < 20){                     // Obstacle near Left Sensor - avoid it by turning Right
      robot.FaceRight();
   }else if(RightSensor < 20){                    // Obstacle near Right Sensor - avoid it by turning Left
      robot.FaceLeft();
   }
   
}
