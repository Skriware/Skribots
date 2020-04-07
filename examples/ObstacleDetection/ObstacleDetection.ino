/* In this example robot has got two rotors (one for each side), distance sensor
 * and three LEDs showing distance from the nearest obstacle in front of it. 
 * 
 * Robot moves forward if there is no obstacle in front of it,
 * gives a warninig if somthing is close,
 * and stops 20 cm from obstacle to avoid collision.
 * 
 * Robot uses one distance sensor plugged to the D1 slot on the EDU Shield
 * and two leds to send light signals.
 * 
 * IMPORTANT!!!
 * The timings for the turns are example values.
 * When building own robot you should do some tests to set the good
 * and working turning times.
 */

#include <Skribot.h>

Skribot robot; // Define our hero.
int distance; // Variable to keep distance from the obstacle.

void setup() {
  // Add the rotors for movement.
  // "LEFT" and "RIGHT" tags let the robot know
  // that rotors are conncted to the Skriware EDU Shield.
  robot.AddDCRotor("LEFT");          
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(100); // Set the maximum speed.
  
  // Add LEDs
  robot.AddLED("LED1"); 
  robot.AddLED("LED2");

  // Add a distance sensor plugged to the D1 slot on the Skriware EDU Shield.
  robot.AddDistSensor("D1");         
}

void loop() {
  // Read the distance to the nearest obstacle
  // with our previously defined sensor on slot D1 on the EDU shield

  distance = robot.ReadDistSensor("D1");

  if (distance > 50) {
    // If no obastacle is in range,
    // go continuously forward and set the green color for the led.
    robot.TurnLEDOn(0,255,0);
    robot.SetSpeed(100);
    robot.MoveForward();
  } else if (distance < 50 && distance > 20) {
    // If an obastacle is in range,
    // go forward but be careful
    // (slow down, and display blue color on both leds).
    robot.TurnLEDOn(0,0,255); 
    robot.SetSpeed(80);
    robot.MoveForward();
  } else if (distance < 20) {
    // If an obastacle is too close,
    // STOP the robot and set red alarm leds.
    robot.TurnLEDOn(255,0,0);
    robot.Stop();
  }
}
