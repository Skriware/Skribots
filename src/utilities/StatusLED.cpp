#include "StatusLED.h"
#define STATUS_LED_INTENSIVITY 100
#ifndef ESP_H
StatusLED::StatusLED(byte R, byte G, byte B,byte batery){
	 R_pin = R;
	 G_pin = G;
	 B_pin = B;	
	 Battery_pin = batery;
	 pinMode(R_pin,OUTPUT);
	 pinMode(G_pin,OUTPUT);
	 pinMode(B_pin,OUTPUT);
	 Current_color = OFF;
	 pinMode(Battery_pin,INPUT);
}
void StatusLED::TurnOn(color _color){
if(_color != Current_color){
	switch(_color){
	case RED:
 	 digitalWrite(R_pin,LOW);
	 digitalWrite(G_pin,HIGH);
	 digitalWrite(B_pin,HIGH);
	break;
	case GREEN:
 	 digitalWrite(R_pin,HIGH);
	 digitalWrite(G_pin,LOW);
	 digitalWrite(B_pin,HIGH);
	break;
	case BLUE:
 	 digitalWrite(R_pin,HIGH);
	 digitalWrite(G_pin,HIGH);
	 digitalWrite(B_pin,LOW);
	break;
	case YELLOW:
 	 digitalWrite(R_pin,LOW);
	 digitalWrite(G_pin,LOW);
	 digitalWrite(B_pin,HIGH);
	break;
	case PURPLE:
 	 digitalWrite(R_pin,LOW);
	 digitalWrite(G_pin,HIGH);
	 digitalWrite(B_pin,LOW);
	break;
	case WHITE:
 	 digitalWrite(R_pin,LOW);
	 digitalWrite(G_pin,LOW);
	 digitalWrite(B_pin,LOW);
	break;
	case OFF:
	 digitalWrite(R_pin,HIGH);
	 digitalWrite(G_pin,HIGH);
	 digitalWrite(B_pin,HIGH);
	break;
	default:
	break;
	}
	Current_color = _color;
}
}
#else
StatusLED::StatusLED(byte LED_PIN,byte batery){
	status = new RobotLED(LED_PIN,0, 2);
	Current_color = OFF;
	Battery_pin = batery;
	pinMode(Battery_pin,INPUT);
}
void StatusLED::TurnOn(color _color,byte NLED){
if(_color != Current_color){
	switch(_color){
	case RED:
 		status->turnON(STATUS_LED_INTENSIVITY,0,0,NLED);
	break;
	case GREEN:
 	 	status->turnON(0,STATUS_LED_INTENSIVITY,0,NLED);
	break;
	case BLUE:
 	 	status->turnON(0,0,STATUS_LED_INTENSIVITY,NLED);
	break;
	case YELLOW:
 	 status->turnON(STATUS_LED_INTENSIVITY,STATUS_LED_INTENSIVITY,0,NLED);
	break;
	case PURPLE:
 	status->turnON(STATUS_LED_INTENSIVITY,0,STATUS_LED_INTENSIVITY,NLED);
	break;
	case WHITE:
 	status->turnON(STATUS_LED_INTENSIVITY,STATUS_LED_INTENSIVITY,STATUS_LED_INTENSIVITY,NLED);
	break;
	case OFF:
	 status->turnON(0,0,0,NLED);
	break;
	default:
	break;
	}
	Current_color = _color;
}
}
#endif
int StatusLED::CheckBateryStatus(){
	#ifdef ESP_H
	float Voltage;
	byte yy = 0;
	for(int ii = 0 ; ii <100;ii++){
		if(digitalRead(Battery_pin) == HIGH){
			yy++;
		}	
	}
	if(yy > 95){
		Voltage = 12.0;
	}else{
		Voltage = 0.0;
	}
	#else
	float mult = 0.005*3;
	float Voltage = (float)analogRead(Battery_pin)*mult;
	Serial.println(Voltage);
	#endif
	if(Voltage > FULL_BateryLevel){
		TurnOn(GREEN);
		return(0);	
	}else if(Voltage > USED_BateryLevel){
		TurnOn(YELLOW);
		return(1);
	}else{
		TurnOn(RED);
		return(2);
	}
}
void StatusLED::BLINK_OK(){
	 TurnOn(OFF);
	 delay(200);
	 TurnOn(WHITE);
	 delay(200);
	 TurnOn(OFF);
	 delay(200);
	 TurnOn(WHITE);
	 delay(200);
	 TurnOn(OFF);
	 delay(200);
	 TurnOn(WHITE);
	 delay(200);
	 TurnOn(OFF);
	 delay(200);
}