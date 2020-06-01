/* In this example we present the commands used for claw operations.
 *
 * Robot will wait for the signal form one of its distance detectors
 * and will perform all avaliable claw operations in a sequence.
 * 
 * Connections for the robot:
 * 
 * In this example robot has got two distance sensors
 * plugged through the Skriware EDU Shield.
 * 
 * Distance detectors need two pins to be connected:
 * 
 * The detector on the left side of the robot:
 *    D1 slot on Skriware EDU Shield.
 * 
 * The detector on the Right Side of the robot:
 *    D2 slot on Skriware EDU Shield.
 *
 * Additonaly, the robot has got a claw plugged into the claw slots
 * on the Skriware EDU Shield.
 */

#include <Skribot.h>

Skribot robot;               // Define our hero.
int LeftSensor, RightSensor; // Variables to keep the measurements form the detectors.

void setup() {
  robot.SetSpeed(100); // Set the maximum speed.

  // Add the distance sensors at slots D1 and D2 on the Skriware EDU shield.
  robot.AddDistSensor("D1");
  robot.AddDistSensor("D2");
  robot.AddClaw();
}

void loop() {
  // Read the distance to the nearest obstacle from both distance sensors.
  // The obtained distance is in cm.
  LeftSensor = robot.ReadDistSensor("D1");       
  RightSensor = robot.ReadDistSensor("D2");  

  if (LeftSensor < 20 || RightSensor < 20) {
    // If there is something near, close the claw and lift it up.
    robot.CloseClaw();
    robot.Pick_Up();
  } else {
    // If there's nothing in range, open the claw and set it to the normal position.
    robot.OpenClaw();
    robot.Put_Down();
  }
}
