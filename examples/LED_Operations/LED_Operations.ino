/*In this example the robot has got two LEDs which he uses to send
 * multicolor light signals.
 * 
 * When sending the color configuration to the robot you need to send it in
 * RGB (RED, GREEN, BLUE) format. You set the color of each LED by sending
 * three numbers coresponding to the three basic colors.
 */

#include <Skribot.h>

Skribot robot; // Define our hero.
  
void setup() {
  // Add the LEDs plugged to the LED1 and LED2 slots on the Skriware EDU shield.
  robot.AddLED("LED1"); 
  robot.AddLED("LED2");
}

void loop() {
  robot.TurnLEDOn(255, 255, 255); // Set the both LEDs to white.
  delay(2000);                    // Wait for 2000 ms (2 s).

  robot.TurnLEDOn(255, 0, 0, "LED1"); // Turn on the LED plugged to the LED1 slot and set red light color.
  robot.TurnLEDOn(0, 255, 0, "LED2"); // Turn on the LED plugged to the LED2 slot and set green light color.
  delay(2000);

  robot.TurnLEDOff("LED1"); // Turn off the LED plugged to the LED1 slot.
  delay(2000);

  robot.TurnLEDOn(255, 255, 0); // Turn on both the LEDs on and set the color to yellow.
  delay(2000);

  robot.TurnLEDOff(); // Turn both LEDs off.
  delay(2000);
}
