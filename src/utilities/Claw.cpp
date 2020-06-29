#include <Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_
#include "Claw.h"

Claw::Claw(int Claw_Pin,int Arm_Pin,byte _id){
	
	#ifdef ESP_H
	SetNewPWMChannel(Claw_Pin);
	SetNewPWMChannel(Arm_Pin);
	claw_pin = Claw_Pin;
	arm_pin = Arm_Pin;
	#else
	claw_servo  = new Servo();
	claw_servo->attach(Claw_Pin);
	arm_servo  = new Servo();
	arm_servo->attach(Arm_Pin);
	#endif
	id = _id;
	up_v = BV_1_up;
	down_v = BV_1_down;
	close_v = BV_1_close;
	open_v = BV_1_open;
}


void Claw::SetAngle(int claw_angle,int arm_angle){
	#ifdef ESP_H
	PWM_Write(claw_pin,claw_angle);
	PWM_Write(arm_pin,arm_angle);
	#else
	claw_servo->write(claw_angle);
	arm_servo->write(arm_angle);
	#endif
}
	void Claw::Close(){	
		#ifndef ESP_H 
		claw_servo->write(close_v);
		#else
		PWM_Write(claw_pin,close_v);
		#endif

	}
	void Claw::Open(){
		#ifndef ESP_H 
		claw_servo->write(open_v);
		#else
		PWM_Write(claw_pin,open_v);
		#endif
	}
	void Claw::Pick_Up(){
		#ifndef ESP_H 
		arm_servo->write(up_v);
		#else
		PWM_Write(arm_pin,up_v);
		#endif
	}
	void Claw::Put_Down(){
		
		#ifndef ESP_H 
		arm_servo->write(down_v);
		#else
		PWM_Write(arm_pin,down_v);
		#endif
	}

void Claw::SetPositions(byte _up_v,byte _down_v,byte _open_v,byte _close_v){
	up_v   = _up_v;
	down_v = _down_v;
	close_v = _close_v;
	open_v = _open_v;
}

byte Claw::GetID(){
	return(id);
}

#endif