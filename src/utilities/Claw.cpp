#include <Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_
#include "Claw.h"

Claw::Claw(int Claw_Pin,int Arm_Pin,byte _id){
	
	
	#ifdef ARDUINO_ARCH_ESP32
	SetNewPWMChannel(Claw_Pin);
	SetNewPWMChannel(Arm_Pin);
	claw_pin = Claw_Pin;
	arm_pin = Arm_Pin;
	#else
	claw_servo  = new Servo();
	claw_servo->attach(Claw_Pin);
	Open();
	arm_servo  = new Servo();
	arm_servo->attach(Arm_Pin);
	Put_Down();
	#endif
	id = _id;
}


void Claw::SetAngle(int claw_angle,int arm_angle){
	#ifdef ARDUINO_ARCH_ESP32
	PWM_Write(claw_pin,claw_angle);
	PWM_Write(arm_pin,arm_angle);
	#else
	claw_servo->write(claw_angle);
	arm_servo->write(arm_angle);
	#endif
}
	void Claw::Close(){	
		#ifndef ARDUINO_ARCH_ESP32 
		claw_servo->write(120);
		#else
		PWM_Write(claw_pin,120);
		#endif

	}
	void Claw::Open(){
		#ifndef ARDUINO_ARCH_ESP32 
		claw_servo->write(170);
		#else
		PWM_Write(claw_pin,170);
		#endif
	}
	void Claw::Pick_Up(){
		
		#ifndef ARDUINO_ARCH_ESP32 
		arm_servo->write(50);
		#else
		PWM_Write(arm_pin,120);
		#endif
	}
	void Claw::Put_Down(){
		
		#ifndef ARDUINO_ARCH_ESP32 
		arm_servo->write(10);
		#else
		PWM_Write(arm_pin,70);
		#endif
	}

byte Claw::GetID(){
	return(id);
}

#endif