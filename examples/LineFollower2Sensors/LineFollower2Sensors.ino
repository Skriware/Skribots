/* In this example we present the basic algorithm for the line follower
 * with two line sensors. The robot will go forward if both sensors don't see
 * any line or turn if any of them do.
 * We want our robot to keep line between sensors.
 * 
 * Connections for the robot:
 * 
 * Line sensor plugged to the L1 slot on Skriware EDU shield
 *    - this sensor needs to be placed on the left side of the robot.
 * Line sensor plugged to the L2 slot on Skriware EDU shield
 *    - this sensor needs to be placed on the right side of the robot. 
 * Two rotors plugged through the Skriware EDU Shield,
 * LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * IMPORTANT!!!
 * Timings for turns are example values.
 * When building own robot you should
 * do some tests to set the good and working turning times.
 */

#include <Skribot.h>

Skribot robot;
bool LEFTSens, RIGHTSens; // Variables to keep the sensor measurements.
                        
void setup() {
  robot.AddLineSensor("L1"); // Add the line sensor.
  robot.AddLineSensor("L2");
  
  // Add the rotors for movement.
  robot.AddDCRotor("LEFT");
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(100); // Set the maximum speed.
}

void loop() {
  LEFTSens  = robot.ReadLineSensor("L1"); // Reading from the first sensor.
  RIGHTSens = robot.ReadLineSensor("L2"); // Reading from the second sensor.
  
  if (!LEFTSens && !RIGHTSens) { // Check if both sensors are detecting the line below it.
    robot.MoveForward(); // Go forward.
  } else if (LEFTSens) {                                 
    robot.TurnLeft(200); // Turn left.
  } else if (RIGHTSens) { // Read the second sensor value.
    robot.TurnRight(200); // Turn right.
  }
}
