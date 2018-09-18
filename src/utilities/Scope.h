#ifndef Scope_H
#define Scope_H
#include "Arduino.h"
#include "DistSensor.h"
#ifndef ESP_H
#include <Servo.h>
#endif

	class Scope
{
public:
	Scope(int EP,int Trigg,int Servo, String Name);
	void SetAngle(int angle);
	int GetDistance();
	String GetName();
private:
	#ifndef ESP_H
	Servo *servo;
	#endif
	DistSensor *sensor;
	String name;
	int servoPin;
};

#endif