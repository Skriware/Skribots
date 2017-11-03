#include "Rotor.h"

Rotor::Rotor(int SpeedPin,int DirectionPin){
	_speed_pin 	= SpeedPin;
	_dir_pin 	= DirectionPin;
	pinMode(_speed_pin, OUTPUT);
	pinMode(_dir_pin, OUTPUT);
	SetSpeed(125);
	SetDirection(1);
}

void Rotor::SetSpeed(int speed){
	_speed = speed;
}

void Rotor::Move(){
	digitalWrite(_dir_pin,_dir);
	analogWrite(_speed_pin,abs(_dir*255-_speed));
}

void Rotor::Stop(){
	if(_dir){
	digitalWrite(_dir_pin,_dir);
	analogWrite(_speed_pin,255);
	}else{
	digitalWrite(_dir_pin,_dir);
	analogWrite(_speed_pin,0);
	}
}

void Rotor::SetDirection(int dir){
	_dir = dir;
}

int Rotor::GetSpeed(){
	return(_speed);
}

int Rotor::GetDirection(){
	return(_dir);
}