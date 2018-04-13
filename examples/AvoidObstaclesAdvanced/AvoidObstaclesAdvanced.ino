#include <Skribot.h>
 /* In this example we present the more advance obstacle avoiding algorithm, which is more complexed then the basic 
 *  form and allows our robot to escape from cornerners and avoid difficult obstacles.
 *  
 *  We decide which way to turn by comparing sesnors readouts not simply turning if we see anything. 
 *  
 *  If there will be a situaton that the robot will turn left after turning right we are probably in the corner... 
 *  It's time to make a big turn and get away! See the code below for details
 * 
 * Connections for robot:
 * 
 * For this example robot has got two rotors plugged by Skriware EDU Shield, LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * Distance detectors needs two pins to be conected:
 * 
 * Detector on the Left Side of the robot: D1 slot on Skriware EDU Shield.
 * 
 * Detector on the Right Side of the robot: D2 slot on Skriware EDU Shield.
 *
 * WARNING!!!: You need to make tests to set optimal angle od distance detectors. 
 * Pointing them right ahead is not always the best option...
 *
 */
  Skribot robot;                                  //defining our hero
  int LeftSensor,RightSensor;                     // variables to keep measurements form detectors. 
  int lastRightSensor, lastLeftSensor;            // variables to keep measurements from previous algorithm step.
void setup() {

  robot.AddDCRotor("LEFT");          //adding rotors for movement
  robot.AddDCRotor("RIGHT");

  robot.SetSpeed(250);               // set maximum speed
  
  robot.AddDistSensor("D1");         //adding Distance sensor on slots D1 and D2 on Skriware EDU shield
  robot.AddDistSensor("D2");

}

void loop() {
   LeftSensor = robot.ReadDistSensor("D1");                  //Read distance to neares obstacle from both sensors distance. Obtained distance is in cm.
   RightSensor = robot.ReadDistSensor("D2");       
    if(LeftSensor > RightSensor){                             //checking previous readout
        if(RightSensor > lastRightSensor){        
          robot.FaceRight(300);                               // Turning Right  
        }else{
          robot.FaceLeft(600);                                 // We turned Left and now we are turning Right again?! We are probably in the corner lets escape!
        } 
    }
    if(RightSensor > LeftSensor){
      if(LeftSensor > lastLeftSensor ){
        robot.FaceLeft(300);                                 // Turning Left
      }
      else{
        robot.FaceRight(1200);                                 // We turned Right and now we are turning Left again?! We are probably in the corner lets escape!
      }
    }
    else{
      robot.MoveForward();                                   //Move Forward if there are no obstacles in th way.                                 
    }
    lastRightSensor = RightSensor;
    lastLeftSensor = LeftSensor;                             //Remembering last readouts

}
