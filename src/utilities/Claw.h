#ifndef Claw_H
#define Claw_H
#include "Arduino.h"
#include <Servo.h>

	class Claw
{
public:
	Claw(int Claw_Pin,int Arm_Pin,byte id = 0);
	void SetAngle(int claw_angle,int arm_angle);
	void Close();
	void Open();
	void Pick_Up();
	void Put_Down();
	byte GetID();
private:
	Servo 	*claw_servo;
	Servo 	*arm_servo;
	byte id;
};

#endif