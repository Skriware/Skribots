/* In this example the robot has got two rotors (one for each side).
 * 
 * Turning vs. Facing:
 * As you can see, there are two functions that you can use for turning: Face and Turn.
 * Face will rotate the robot in place (both wheels will rotate but in different directions).
 * Turning means that only one wheel is turning while the other stands still.
 *
 * IMPORTANT!!!
 * The timings for the turns are example values.
 * when building your own robot you should do some tests to set
 * the good and working turning times.
 */

#include <Skribot.h>
 
Skribot robot; // Define our hero.

void setup() {
  // Add the rotors for movement.
  // "LEFT" and "RIGHT" tags let the robot know
  // that rotors are conncted to the Skriware EDU Shield.
  robot.AddDCRotor("LEFT");          
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(100); // Set the maximum speed.
}

void loop() {
  robot.MoveForward(2000); // Go forward for 2000 ms (2 seconds).
  robot.FaceRight(1000);   // Face right for 1 s (both rotors are moving).
  robot.MoveForward(2000); // Go Forward for 2 seconds.
  robot.TurnLeft(1000);    // Turn Left for 1 s (only one rotor is moving).
}
