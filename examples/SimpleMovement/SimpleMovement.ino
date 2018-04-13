#include <Skribot.h>

/*In this example robot has got two rotors one for each side. 
 *  For this example robot has got two rotors plugged by Skriware EDU Shield, LEFT and RIGHT rotors are plugged to the rotors connections.
 * 
 * Turning vs. Facing:
 * As you can see there are two functions thath you can use for turning: Face and Turn. Face will rotate robot in place (Both wheels will rotate but in different directions.). Turning means that only one wheel is turning while the other stands still.
 *
 *
 * IMPORTANT!!!
 * Timmings for turns are set for example values, when building own robot you should do some tests to set good working turning times.
 */
 
Skribot robot;                      //defining our hero

void setup() {
  
    robot.AddDCRotor("LEFT");          //adding rotors for movement "LEFT" and "RIGHT" tags let the robot know that rotors are conncted to the Skriware EDU Shiels
    robot.AddDCRotor("RIGHT");
    robot.SetSpeed(250);               // seting movment speed for mximal one(the range is form 0 to 250)
    
}
void loop() {
        
        robot.MoveForward(2000);             //Go forward for 2s 
        
        robot.FaceRight(1000);               //Face Left for 1s -> stay in place and face to the left ( both rotors are moving)
        
        robot.MoveForward(2000);             //Go Forward for 2s
        
        robot.TurnLeft(1000);                //Turn Left for 1s -> move in the left direction (only one rotor is moving) 
        
}
