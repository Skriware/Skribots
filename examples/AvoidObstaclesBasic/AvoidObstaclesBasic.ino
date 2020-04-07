/* In this example we present the simplest obstacle avoiding algorithm:
 * 
 * If you see an obstacle on the right side - Turn Left
 * If you see an obstacle on the left  side - Turn Right 
 * 
 * Connections for the robot:
 * 
 * In this example robot has got two rotors plugged through Skriware EDU Shield,
 * LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * Distance detectors needs two pins to be conected:
 * 
 * Detector on the left side of the robot: D1 slot on the Skriware EDU Shield.
 * 
 * Detector on the right side of the robot: D2 slot on the Skriware EDU Shield.
 *
 * WARNING!!!: You need to make tests to set optimal angle of the distance
 * detectors. Pointing them right ahead is not always the best option...
 *
 */

#include <Skribot.h>

Skribot robot;               // Define our hero.
int LeftSensor, RightSensor; // Variables to keep measurements form detectors.

void setup() {
  // Add the rotors to the robot for movement.
  robot.AddDCRotor("LEFT");
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(100); // Set the maximum speed.

  // Add the distance sensors at slots D1 and D2 on the Skriware EDU shield.
  robot.AddDistSensor("D1");
  robot.AddDistSensor("D2");
}

void loop() {
  // Read the distance to nearest obstacle from both distance sensors.
  // The obtained distance is in cm.
  LeftSensor = robot.ReadDistSensor("D1");       
  RightSensor = robot.ReadDistSensor("D2");  

  if (LeftSensor > 20 && RightSensor > 20) {
     // There is no obstacles near both sensors - move forward.
     robot.MoveForward();
  } else if (LeftSensor < 20) {
     // Obstacle near the left sensor - avoid it by turning right.
     robot.FaceRight();
  } else if (RightSensor < 20) {
     // Obstacle near the right sensor - avoid it by turning Left.
     robot.FaceLeft();
  }
}
