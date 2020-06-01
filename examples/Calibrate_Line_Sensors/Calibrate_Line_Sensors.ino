#include "Skribot.h"
Skribot robot;
void setup() {
  robot.Set_Line_Sensor_Logic_Border("L1",0,500); // Sesnor ID , line readout, no line readout
  robot.Set_Line_Sensor_Logic_Border("L2",0,500);
  robot.Set_Line_Sensor_Logic_Border("L3",0,500);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}