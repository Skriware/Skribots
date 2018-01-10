#include <SkriBot.h>
 /* In this example we present commnads used for claw operations
 * 
 Robot will wait for the signal form one of its distance detectors and perform all avaliable Claw operations in a sequence.
 * 
 * Connections for robot:
 * 
 * For this example robot has got two Distance sensors plugged by Skriware EDU Shield,.
 * 
 * Distance detectors needs two pins to be conected:
 * 
 * Detector on the Left Side of the robot: D1 slot on Skriware EDU Shield.
 * 
 * Detector on the Right Side of the robot: D2 slot on Skriware EDU Shield.
 *
 * Additonaly robot has got a claw plugged into the claw slots on Skriware EDU Shield.
 */
  SkriBot robot;                                  //defining our hero                   // variables to keep measurements form detectors 
void setup() {

  robot.SetSpeed(250);               // set maximum speed
  
  robot.AddDistSensor("D1");         //adding Distance sensor on slots D1 and D2 on Skriware EDU shield
  robot.AddDistSensor("D2");
  robot.AddClaw();

}

void loop() {
   LeftSensor = robot.ReadDistSensor("D1");       //Read distance to neares obstacle from both sensors distance. Obtained distance is in cm.
   RightSensor = robot.ReadDistSensor("D2");  

   if(LeftSensor < 20 || RightSensor < 20){       // If there is somthing near close claw and lift it up.
      robot.CloseClaw();
      robot.Pick_Up();
   }else{                                         // if nothing in range open claw and set it to normal position.
      robot.OpenClaw();
      robot.Put_Down();
   }
   
}
