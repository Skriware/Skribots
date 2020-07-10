#ifndef STATUSLED_H
#define STATUSLED_H
#include "Arduino.h"
#ifdef ESP_H
#include "RobotLED.h"
#endif
#define FULL_BateryLevel 11.5//8.6
#define USED_BateryLevel 11.0//8.2


enum color {RED = 0,GREEN = 1,BLUE = 2,YELLOW = 3,WHITE = 4,PURPLE = 5,OFF = 6};
	class StatusLED
{
public:
	#ifndef ESP_H
	StatusLED(byte R_pin,byte G_pin,byte B_pin,byte Battery_pin);
	void TurnOn(color _color);
	#else
	StatusLED(byte LED_pin,byte Battery_pin,byte Board_V);
	void TurnOn(color _color,byte nLED=1);
	#endif
	int CheckBateryStatus();
	byte ReadBatteryState();
	void BLINK_OK();
private:
	#ifndef ESP_H
		byte R_pin;
		byte G_pin;
		byte B_pin;	
	#else
		RobotLED *status = NULL;
		byte Board_V;
		float Current_voltage = 0.0;	
	#endif
	byte Battery_pin;
	color Current_color;
	
};

#endif