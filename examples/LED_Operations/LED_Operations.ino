#include <Skribot.h>

/*In this example robot has got two LEDs which he uses to send multicolor light signals.
 * 
 * When sending color configuration to the robot you need to send it in RGB(RED,GREEN,BLUE) format. You set the color by sending 3 numbers to the LED each coresponding to one of three basic colors.
 */

  Skribot robot;    //defining our hero
  
void setup() {
  
    robot.AddLED("LED1");              // Adding LEDs plugged to LED1 na LED2 slots on the Skriware EDU shield.
    robot.AddLED("LED2");

}

void loop() {
    robot.TurnLEDOn(255,255,255);     // Turning Both LEDs on white color.

    delay(2000);                      // wait for 2000 ms (2 s)
    robot.TurnLEDOn(255,0,0,"LED1");  // Turn LED plugged to slot LED1 and set red light color.


    robot.TurnLEDOn(0,255,0,"LED2");  // Turn LED plugged to slot LED2 and set green light color.

    delay(2000);

    robot.TurnLEDOff("LED1");         // Turn Off LED plugged to slot LED1.

    delay(2000);

    robot.TurnLEDOn(255,255,0);       // Turn both LED on and set color to yellow.

    delay(2000);

    robot.TurnLEDOff();               //Turn both LEDs off;

    delay(2000);
}