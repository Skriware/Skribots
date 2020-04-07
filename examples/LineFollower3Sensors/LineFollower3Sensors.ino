/* In this example we present the line folower which uses three sensors
 * from the LineSenosor bar. We can read specific values for each of the
 * 3 detectors in the bar: left, right and center, instead of reading from
 * all of them as one. 
 * 
 * Algorithm is explained in comments below.
 * 
 * Connections for robot:
 * 
 * Line sensor plugged to the L1 slot on the Skriware EDU shield:
 *      - this sensor needs to be placed on the left side of the robot.
 * Line sensor plugged to the L2 slot on the Skriware EDU shield:
 *      - this sensor needs to be placed on the right side of the robot. 
 * Line sensor plugged to the L3 slot on the Skriware EDU shield:
 *      - this sensor needs to be placed on the center of the robot.
 * Two rotors plugged by Skriware EDU Shield:
 *      LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * IMPORTANT!!!
 * The timings for the turns are example values.
 * When building your own robot, you should do some tests to set the good
 * and working turning times.
 */

#include <Skribot.h>
Skribot robot;

// Variables to keep sensor measurements.
bool LeftSensor;
bool RightSensor;
bool CenterSensor;

void setup() {
  // Add the line sensors.
  robot.AddLineSensor("L1");
  robot.AddLineSensor("L2"); 
  robot.AddLineSensor("L3");      
  
  // Add the rotors for movement.
  robot.AddDCRotor("LEFT");
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(100);
}

void loop() {
  // Reading the line sensors.
  LeftSensor = robot.ReadLineSensor("L1");
  CenterSensor = robot.ReadLineSensor("L2");
  RightSensor = robot.ReadLineSensor("L3");
	
  if(!LeftSensor && !RightSensor && CenterSensor){
    //if we see line on the middle sensor we can proceed forward
    robot.MoveForward();
  } else if (LeftSensor) {
    // Line is on the Left. We want to have it in the middle - let's turn Right!
    robot.FaceLeft(150);                                                         
  } else if (RightSensor) {
    // Line is on the Right. We want to have it in the middle - let's turn Left!
    robot.FaceRight(150);                                                     
  } else if (CenterSensor && RightSensor) {
    // Sharp right turn
    robot.FaceRight(300);
  } else if (LeftSensor && CenterSensor) {
    // Sharp left turn
    robot.FaceLeft(300);
  } else {
  	robot.FaceRight(100);
  }
}
