#ifndef Claw_H
#define Claw_H
#include "Arduino.h"
#include "PWM_Handler.h"
#ifndef ESP_H
#include <Servo.h>
#endif


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
	#ifndef ESP_H
	Servo 	*claw_servo;
	Servo 	*arm_servo;
	#endif
	byte claw_pin;
	byte arm_pin;
	byte id;
};

#endif