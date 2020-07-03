/* In this example the robot has got two rotors (one for each side) You can controll each motor individually 
 * using the "Set_Motor_Movment" function. You can control both rotors at once if you omiit the "time" parameter.
 * 
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

}

void loop() {
  robot.Move_Motor_Forward(LEFT,100,3000); //move Left rotor forward for 3s and 100% speed 
  robot.Move_Motor_Back(RIGHT,50,5000);    //move Right rotor back for 5s and 50% speed  
  robot.Move_Motor_Forward(RIGHT,50);
  robot.Move_Motor_Back(LEFT,50);          // setting rotors to move continously.
  delay(5000);                             // wait for robot movment.
  robot.Stop();                            //Stopping the robot.
  delay(2000);                             //wait fo next interation.
}
