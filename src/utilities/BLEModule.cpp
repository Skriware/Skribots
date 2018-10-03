#include <Arduino.h>
#ifndef _VARIANT_BBC_MICROBIT_
#include "BLEModule.h"
#include <EEPROM.h>

#ifdef ESP_H

bool BLEModule::deviceConnected = false;
char BLEModule::RXBLE_buffer[BLERXBUFFER_SIZE];
byte BLEModule::RXBLE_buffer_iterator_end = 1;
byte BLEModule::RXBLE_buffer_iterator_beg = 0;
#endif 


BLEModule::BLEModule(moduleType type){
	_type = type;
}

char BLEModule::BLE_read(){
	  	char tmp;

switch(_type){
		case HM_10:
		#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
			tmp = Serial3.read();
			#endif
		break;
		case RN4020:
			#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
			tmp = RN4020_read();
			#endif
		break;
	case ESP32_BLE:

		#ifdef ESP_H
		if(BLERXBUFFER_SIZE - substractBufforIterators() > 0){
			incrementRXbuffIterator_beg();
	        tmp = RXBLE_buffer[RXBLE_buffer_iterator_beg];
		}else{
		tmp = 'Q';
		}
		#endif
		break;
		default:
		break;
	}
	    return(tmp);
  }
  
void BLEModule::BLE_write(char *msg){
	#ifdef ESP_H
		std::string _tmp = std::string(msg);
	#endif
	switch(_type){
		case HM_10:
			#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
    		Serial3.println(msg);
    		#endif
    		break;
    	case RN4020:
    		#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
    		RN4020_write(msg);
    		#endif
    		break;
    	case ESP32_BLE:
    	#ifdef ESP_H
    		 TxCharacteristic->setValue(_tmp);
        	 TxCharacteristic->notify();
			#endif
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
			#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
			connection = RN4020_checkConnection();
			#endif
			break;
		case ESP32_BLE:
		#ifdef ESP_H
			connection = BLEModule::deviceConnected;
		#endif
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
			#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
    		dataAvalible = Serial3.available();
    		#endif
    		 break;
    	case RN4020:
    		#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
    		dataAvalible = RN4020_dataAvailable();
    		#endif
    		break;
    	case ESP32_BLE:

    	#ifdef ESP_H
    		dataAvalible = BLERXBUFFER_SIZE - substractBufforIterators()-1;
    	#endif

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
		#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
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
		   #endif
     break;
     case RN4020:
     	#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
     	  RN4020_Setup();
     	  #endif
     	break;
    case ESP32_BLE:
    #ifdef ESP_H
    	  // Create the BLE Device
    
  		 BLEDevice::init("Skri");
  

  		  Server = BLEDevice::createServer();

  		  Server->setCallbacks(new MyServerCallbacks());

    	  Service = Server->createService(SERVICE_UUID);

    	  
    	  RxCharacteristic = Service->createCharacteristic(
											 CHARACTERISTIC_UUID_RX,
											BLECharacteristic::PROPERTY_WRITE_NR);

    	  RxCharacteristic->setCallbacks(new MyCallbacks());

    	  TxCharacteristic = Service->createCharacteristic(
										CHARACTERISTIC_UUID_TX,
										BLECharacteristic::PROPERTY_NOTIFY
									);

    	  TxCharacteristic->addDescriptor(new BLE2902());

    	  Service->start();

  			// Start advertising
    	  Server->getAdvertising()->addServiceUUID(BLEUUID(SERVICE_UUID));
  		  Server->getAdvertising()->start();

    #endif
    	break;
	default:
	 break;
	}

  }

  void BLEModule::BLE_changeName(char *name, bool userConncection){
	  switch(_type){
			case HM_10:

				 #ifndef ESP_H && _VARIANT_BBC_MICROBIT_
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
				   #endif
				break;
			case RN4020:
				#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
				RN4020_changeName(name);
				#endif
				break;
			case ESP32_BLE:

			#ifdef ESP_H

			#endif

				break;
			default:
				break;
		}
}


#ifdef ESP_H

  void incrementRXbuffIterator_end(){
    	if(BLEModule::RXBLE_buffer_iterator_end == BLERXBUFFER_SIZE-1){
    		BLEModule::RXBLE_buffer_iterator_end = 0;
    	}else{
    		BLEModule::RXBLE_buffer_iterator_end++;
    	}
    }

      void incrementRXbuffIterator_beg(){
    	if(BLEModule::RXBLE_buffer_iterator_beg == BLERXBUFFER_SIZE-1){
    		BLEModule::RXBLE_buffer_iterator_beg = 0;
    	}else{
    		BLEModule::RXBLE_buffer_iterator_beg++;
    	}
    }

    byte substractBufforIterators(){
    	if(BLEModule::RXBLE_buffer_iterator_end < BLEModule::RXBLE_buffer_iterator_beg){
    		return(BLEModule::RXBLE_buffer_iterator_beg - BLEModule::RXBLE_buffer_iterator_end);
    	}else if(BLEModule::RXBLE_buffer_iterator_beg < BLEModule::RXBLE_buffer_iterator_end){
    		return(BLERXBUFFER_SIZE - BLEModule::RXBLE_buffer_iterator_end + BLEModule::RXBLE_buffer_iterator_beg);
    	}else{
    		return(0);
    	}
    }

 #endif


  #endif