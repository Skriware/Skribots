#ifndef Scope_H
#define Scope_H
#include "Arduino.h"
#include "DistSensor.h"
#include <Servo.h>

	class Scope
{
public:
	Scope(int EP,int Trigg,int Servo, String Name);
	void SetAngle(int angle);
	int GetDistance();
	String GetName();
private:
	Servo *servo;
	DistSensor *sensor;
	String name;
	int servoPin;
};

#endif