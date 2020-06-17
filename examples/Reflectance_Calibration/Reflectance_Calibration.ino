#include <Skribot.h>

Skribot robot; // Define our hero.
                        
void setup() {
  robot.AddLineSensor("L1"); // Add the line sensor at slot L1 of the Skriware EDU shield.
  robot.AddLineSensor("L2");
  robot.AddLineSensor("L3");
}

void loop() {
robot.SendMessage("L1:");
robot.SendMessage(robot.ReadLineSensorData("L1")); // reading a raw data from Line sensor and sending it to the computer every 200 ms.
robot.SendMessage("L2:");
robot.SendMessage(robot.ReadLineSensorData("L2")); 
robot.SendMessage("L3:");
robot.SendMessageLine(robot.ReadLineSensorData("L3")); 
delay(500);
}
