#include "StatusLED.h"

StatusLED::StatusLED(byte R, byte G, byte B,byte batery){
	 R_pin = R;
	 G_pin = G;
	 B_pin = B;	
	 Battery_pin = batery;
	 pinMode(R_pin,OUTPUT);
	 pinMode(G_pin,OUTPUT);
	 pinMode(B_pin,OUTPUT);
	 TurnOn(OFF);
	 TurnOn(WHITE);
	 delay(200);
	 TurnOn(OFF);
	 delay(200);
	 TurnOn(WHITE);
	 delay(200);
	 TurnOn(OFF);
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
}
}


int StatusLED::CheckBateryStatus(){
	float Voltage = analogRead(Battery_pin)*0.005*3; 
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