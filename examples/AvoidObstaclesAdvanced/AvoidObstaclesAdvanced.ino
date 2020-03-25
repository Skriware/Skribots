/* In this example we present the more advanced obstacle avoiding algorithm,
 * which is more complex then the basic form and allows our robot to escape
 * from corners and avoid difficult obstacles.
 *  
 * Not only we turn if we see an obstacle but we decide which way to turn
 * by comparing the distance sensor readouts.
 *  
 * If there is a situaton in which the robot turns left after turning right
 * we are probably in a corner... 
 * It's time to make a big turn and get away! See the code below for details.
 * 
 * Connections for the robot:
 * In this example robot has got two rotors plugged through Skriware EDU Shield,
 * LEFT and RIGHT rotors are plugged to the rotor connections.
 * 
 * Distance detectors need two pins to be conected:
 * 
 * Detector on the Left Side of the robot: D1 slot on Skriware EDU Shield.
 * 
 * Detector on the Right Side of the robot: D2 slot on Skriware EDU Shield.
 *
 * WARNING!!!: You need to make tests to set an optimal angle of the distance
 * detectors. Pointing them right ahead is not always the best option...
 *
 */

#include <Skribot.h>

Skribot robot;                       // defining our hero
int LeftSensor, RightSensor;         // variables to keep measurements form detectors. 
int lastRightSensor, lastLeftSensor; // variables to keep measurements from previous algorithm step.

void setup() {
  // add the rotors to the robot for movement
  robot.AddDCRotor("LEFT");
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(250); // set maximum speed

  // add distance sensors at slots D1 and D2 on Skriware EDU shield
  robot.AddDistSensor("D1");
  robot.AddDistSensor("D2");
}

void loop() {
  // Read distance to neares obstacle from both sensors distance.
  // The obtained distance is in cm.
  LeftSensor = robot.ReadDistSensor("D1");
  RightSensor = robot.ReadDistSensor("D2");       

  // check the previous readout
  if (LeftSensor > RightSensor) { 
    if (RightSensor > lastRightSensor) {
      robot.FaceRight(300); // Turning Right  
    } else {
      // We turned Left and now we are turning Right again?!
      // We are probably in the corner! Let's escape!
      robot.FaceLeft(600);
    } 
  }

  if (RightSensor > LeftSensor) {
    if (LeftSensor > lastLeftSensor) {
      robot.FaceLeft(300); // Turning Left
    } else {
      // We turned Right and now we are turning Left again?!
      // We are probably in the corner! Let's escape!
      robot.FaceRight(600);
    }
  }
  else {
    robot.MoveForward(); // Move Forward if there are no obstacles in the way.
  }

  // Remember last readouts
  lastRightSensor = RightSensor;
  lastLeftSensor = LeftSensor;
}
