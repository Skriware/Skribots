#include <Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_
#include "BLEModule.h"
#include <EEPROM.h>

BLEModule::BLEModule(moduleType type){
	_type = type;
}

char BLEModule::BLE_read(){
	  	char tmp;

switch(_type){
		case HM_10:
			tmp = Serial3.read();
		break;
		case RN4020:
			tmp = RN4020_read();
		break;
		default:
		break;
	}
	    return(tmp);
  }
  
void BLEModule::BLE_write(char *msg){
	switch(_type){
		case HM_10:
    		Serial3.println(msg);
    		break;
    	case RN4020:
    		RN4020_write(msg);
    		break;
		default:
			break;
	}
  }

bool BLEModule::BLE_checkConnection(){
			 bool connection;  
	switch(_type){
		case HM_10:
			 connection = digitalRead(EDU_BT_STATE_PIN) == HIGH;
			 break;
		case RN4020:
			connection = RN4020_checkConnection();
			break;
		default:
			break;
	}
			 return(connection);
  }

 int BLEModule::BLE_dataAvailable(){
    		int dataAvalible;
    switch(_type){
		case HM_10:
    		dataAvalible = Serial3.available();
    		 break;
    	case RN4020:
    		dataAvalible = RN4020_dataAvailable();
    		break;
		default:
			break;
	}
    		return(dataAvalible);

  }

  void BLEModule::BLE_Setup(){
     byte IfNamed = 0;
    switch(_type){
		case HM_10:
		    Serial3.begin(9600);
		    Serial3.setTimeout(50);
		    pinMode(EDU_BT_STATE_PIN,INPUT);
		    IfNamed = EEPROM.read(10);                         
		    if(IfNamed != 1){
		       char MAC[23] = {' '};
		       delay(100);
		       Serial3.write("AT");
		       delay(100);
		       Serial3.write("AT+ADDR?");
		       delay(100);
		       int MACCounter = 0;
		       while(BLE_dataAvailable()){
		        MAC[MACCounter] = Serial3.read();
		        MACCounter++;
		        if(MACCounter > 23)break;
		       }
		        char tmpmess[32] = {' '};
		       sprintf(tmpmess,"AT+NAMESkribot_%c%c%c",MAC[19],MAC[20],MAC[21]);
		       delay(100);
		       Serial3.write(tmpmess);
		       delay(100);
		       Serial3.write("AT+RESET");
		       delay(100);
		    }else{
		      #ifdef DEBUG_MODE
		      Serial.println("Robot named!");
		      #endif
		    }
     break;
     case RN4020:
     	  RN4020_Setup();
     break;
	default:
	 break;
	}

  }

  void BLEModule::BLE_changeName(char *name, bool userConncection){
	  switch(_type){
			case HM_10:
				  while(BLE_checkConnection()){
				    #ifdef DEBUG_MODE
				    Serial.println("waiting...");
				    #endif
				  }
				    #ifdef DEBUG_MODE
				    Serial.println("disconnected!");
				    #endif
				   char tmpmess[32];
				   delay(100);
				   Serial3.write("AT");
				   delay(100);
				   sprintf(tmpmess,"AT+NAME%s",name);
				   Serial3.write(tmpmess);
				   delay(100);
				   Serial3.write("AT+RESET");
				   delay(100);
				   if(userConncection)EEPROM.write(10,1);
				break;
			case RN4020:
				RN4020_changeName(name);
				break;
			default:
				break;
		}
}

  #endif