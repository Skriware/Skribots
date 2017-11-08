#include "Claw.h"

Claw::Claw(int Claw_Pin,int Arm_Pin,byte _id){
	claw_servo  = new Servo();
	claw_servo->attach(Claw_Pin);
	Open();
	arm_servo  = new Servo();
	arm_servo->attach(Arm_Pin);
	Put_Down();
	id = _id;
}

void Claw::SetAngle(int claw_angle,int arm_angle){
	claw_servo->write(claw_angle);
	arm_servo->write(arm_angle);
}

	void Claw::Close(){
		claw_servo->write(135);
	}
	void Claw::Open(){
		claw_servo->write(180);
	}
	void Claw::Pick_Up(){
		arm_servo->write(50);
	}
	void Claw::Put_Down(){
		arm_servo->write(10);
	}

byte Claw::GetID(){
	return(id);
}