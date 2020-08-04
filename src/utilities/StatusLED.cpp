#include "StatusLED.h"
#define STATUS_LED_INTENSIVITY 30
//#define RANDOM_BATTERY_READ
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
StatusLED::StatusLED(byte LED_PIN,byte batery,byte V){
	status = new RobotLED(LED_PIN,0,2);
	Current_color = OFF;
	Battery_pin = batery;
	Board_V = V;
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
	if(Board_V == 1){
	for(int ii = 0 ; ii <100;ii++){
		if(digitalRead(Battery_pin) == HIGH){
			yy++;
		}	
	}
	
	if(yy > 95){
		Current_voltage = 12.0;
	}else{
		Current_voltage = 0.0;
	}
	}else if(Board_V == 2){
	float mult = 0.004;
	Voltage = 0.004*analogRead(4);
	Serial.print("Batt:");
	Serial.print(Voltage);
	Serial.print("V");
	Current_voltage = Voltage;
	}
	#else
	float mult = 0.005*3;
	Current_voltage = (float)analogRead(Battery_pin)*mult;
	#endif
	ReadBatteryState();
}
byte StatusLED::ReadBatteryState(){
	byte read = (byte)((Current_voltage-9.5)/3.1*100);
	#ifdef RANDOM_BATTERY_READ
	read = millis()%100;
	#endif
	if(read > 50){
		TurnOn(GREEN);
	}else if(read > 20){
		TurnOn(YELLOW);
	}else{
		TurnOn(RED);
	}
	return(read);
}
void StatusLED::BLINK_OK(){
	 for(byte rr = 0;rr<2
	  #ifdef ESP_H 
	 	+Board_V
	 #endif 
	 	;rr++){
	 TurnOn(OFF);
	 delay(200);
	 TurnOn(GREEN);
	 delay(200);
	}
	

}