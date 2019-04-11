#include "Rotor.h"

Rotor::Rotor(int SpeedPin,int DirectionPin){
	#ifndef _VARIANT_BBC_MICROBIT_  
	_speed_pin 	= SpeedPin;
	_dir_pin 	= DirectionPin;
	SetNewPWMChannel(_speed_pin);
	pinMode(_dir_pin,OUTPUT);
	#else
	_dir_pin_1 = SpeedPin;
  	_dir_pin_2 = DirectionPin;
  	pinMode(_dir_pin_1, OUTPUT);
  	pinMode(_dir_pin_2, OUTPUT);
  	digitalWrite(_dir_pin_1,LOW);
	digitalWrite(_dir_pin_2,LOW);
	#endif
	speed_scale = 100;
	SetSpeed(255);
	SetDirection(1);
	invert = false;
}

void Rotor::SetSpeed(int speed){
		_speed = speed*speed_scale/100; 
}
void Rotor::Move(){
byte dir = _dir;
if(invert) dir = abs(dir-1);
#ifndef _VARIANT_BBC_MICROBIT_ 
	digitalWrite(_dir_pin,LOW);
	digitalWrite(_speed_pin,LOW);
	digitalWrite(_dir_pin,dir);
	PWM_Write(_speed_pin,abs(dir*255-_speed+1));
#else	
if(_speed == 0){
	Stop();
}else if(dir == 1){
	digitalWrite(_dir_pin_1,LOW);
	digitalWrite(_dir_pin_2,HIGH);
}else{
	digitalWrite(_dir_pin_2,LOW);
	digitalWrite(_dir_pin_1,HIGH);
}
	#endif
}

void Rotor::invert_rotor(bool inv){
	invert = inv;
}

void Rotor::Stop(){
	
	#ifndef _VARIANT_BBC_MICROBIT_ 
	if(_dir){
		digitalWrite(_dir_pin,_dir);
		PWM_Write(_speed_pin,255);
	}else{
		digitalWrite(_dir_pin,_dir);
		PWM_Write(_speed_pin,0);
	}
	#else
		digitalWrite(_dir_pin_1,LOW);
		digitalWrite(_dir_pin_2,LOW);	
	#endif
}

void Rotor::SetDirection(int dir){
	_dir = dir;
}

int Rotor::GetSpeed(){
	return(_speed);
}

void Rotor::scale_speed(byte _scale){
	 speed_scale = _scale;
}

int Rotor::GetDirection(){
	return(_dir);
}