#include <Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_ 
#ifndef ESP_H
#include "Scope.h"

Scope::Scope(int EP,int Trigg,int ServoPin, String Name){
	sensor = new DistSensor(EP,Trigg,"scope_sense");
	servo  = new Servo();
	servo->attach(ServoPin);
	servo->write(90);
	name = Name;
	servoPin = ServoPin;
}

void Scope::SetAngle(int ang){
	servo->attach(servoPin);
	servo->write(ang);
}

int Scope::GetDistance(){
	return(sensor->RawReadSensor());
}

String Scope::GetName(){
	return(name);
}

#endif
#endif