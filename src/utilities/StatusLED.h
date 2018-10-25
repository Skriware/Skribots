#ifndef STATUSLED_H
#define STATUSLED_H
#include "Arduino.h"
#define FULL_BateryLevel 10.5//8.6
#define USED_BateryLevel 10.0//8.2

enum color {RED = 0,GREEN = 1,BLUE = 2,YELLOW = 3,WHITE = 4,PURPLE = 5,OFF = 6};
	class StatusLED
{
public:
	StatusLED(byte R_pin,byte G_pin,byte B_pin,byte Battery_pin);
	void TurnOn(color _color);
	int CheckBateryStatus();
private:
	byte R_pin;
	byte G_pin;
	byte B_pin;	
	byte Battery_pin;
	color Current_color;
};

#endif