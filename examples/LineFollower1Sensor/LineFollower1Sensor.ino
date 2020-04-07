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

#include <Skribot.h>

Skribot robot; // Define our hero.
                        
void setup() {
  robot.AddLineSensor("L1"); // Add the line sensor at slot L1 of the Skriware EDU shield.

  // Add the rotors for movement.
  robot.AddDCRotor("LEFT");  
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(100); // Set the maximum speed.
}

void loop() {
  // Check if the sensor is detecting the line below it.
  // ReadLineSensor returns 1 (there is a line below) or 0 (there is no line).
  if (robot.ReadLineSensor("L1")) {
    robot.TurnLeft(200);  // Turn left
  } else {
    robot.TurnRight(200); // Turn right  
  }
}
