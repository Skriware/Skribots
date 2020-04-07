#include <Skribot.h>

Skribot robot; // Define our hero.
                        
void setup() {
  robot.AddLineSensor("L1"); // Add the line sensor at slot L1 of the Skriware EDU shield.
  robot.SendMessage("Analog Output from L1 port:");      // Printing static text as header
}

void loop() {
 

robot.SendMessageLine(robot.ReadLineSensorData("L1")); // reading a raw data from Line sensor and sending it to the computer every 200 ms.
delay(200);
}
