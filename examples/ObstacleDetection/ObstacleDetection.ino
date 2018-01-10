#include <SkriBot.h>

/*In this example robot has got two rotors one for each side, distance sensor and three LEDs showing distance from the nearest obstacle in front of it. 
 * 
 * Robot moves forward if there is no obstacle in front of it, gives a warninig if somthing is close, and stops 20 cm from obstacle to avoid collision.
 * 
 * Robot uses one distance sensor plugged to "D1" slot on the edu Shield and two leds to send light signals.
 * 
 * IMPORTANT!!!
 * Timmings for turns are set for example values, when building own robot you should do some tests to set good working turning times.
 */

  SkriBot robot;    //defining our hero
  
  int distance;    //variable to keep distance from the obstacle

void setup() {

    robot.AddDCRotor("LEFT");          // Adding rotors for movement "LEFT" and "RIGHT" tags let the robot know that rotors are conncted to the Skriware EDU Shield.
    robot.AddDCRotor("RIGHT");
    robot.SetSpeed(250);               // Seting movment speed for mximal one(the range is form 0 to 250)
  
    robot.AddLED("LED1");              // Adding LEDs
    robot.AddLED("LED2");

    robot.AddDistSensor("D1");         // Adding distance sensor plugged to the D1 slot on the Skriware EDU Shield 

}

void loop() {

 distance = robot.ReadDistSensor("D1"); 		// Reading distance to the nearest obstacle from our previously defined sensor on slot "D1" on the EDU shield up to 50 cm if nothing in range it returns 25 cm.

       if(distance > 50){
             robot.TurnLEDOn(0,255,0);
             robot.SetSpeed(255);                         // If no obastacle is in range go continuisly forward. And Set green color for the led.
             robot.MoveForward();
       }else if(distance < 50 && distance > 20){
             robot.TurnLEDOn(0,0,255);                   // If  obastacle is in range go forward but be carful (slow down, and display Blue color on both leds).
             robot.SetSpeed(200);
             robot.MoveForward();
       }else if(distance < 20){
             robot.TurnLEDOn(255,0,0);                   // If  obastacle is too close STOP the robot and set red alarm light on leds.
             robot.Stop();
       }
      
}
