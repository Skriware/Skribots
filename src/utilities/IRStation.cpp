#include "Arduino.h"
#ifndef _VARIANT_BBC_MICROBIT_ && ESP_H
#include "IRStation.h"


	
      IRStation::IRStation(int SendPin,int RecvPin,int Address){

      	_Address 	= Address;
      	_SendPin 	= SendPin;

      	irrecv = new IRrecv(RecvPin);

      	irrecv->enableIRIn();				// Starting the reciver

      	irsend = new IRsend();				// Starting the transmiter

      }

      bool IRStation::SendWithConfirmation(int TargetAddress,unsigned long data, byte trialnumber){
      	
      	unsigned long tmp_in;

      	for(int jj = 0; jj < trialnumber; jj++){

		      		Send(TargetAddress,data);
		      		delay(timeIntervalRead);
					    tmp_in = ReadAddressedData();
		
					if(tmp_in == 13){
						return(true);
						break;
					}	
		
		}		

		return(false);

      }

      void IRStation::Send(int TargetAddress,unsigned long data){

      		irsend->sendSony(HeaderId, 12);
					delay(timeIntervalWrite);
					irsend->sendSony(TargetAddress, 12);
					delay(timeIntervalWrite);
					irsend->sendSony(data, 12);
					delay(timeIntervalWrite);
					irsend->sendSony(HeaderId-(data+TargetAddress), 12);
					delay(timeIntervalWrite);

      }

      unsigned long IRStation::ReadIRData(byte trialnumber){
     for(int kk = 0 ; kk < trialnumber; kk++){
      		 if (irrecv->decode(&message)) {
      		 	irrecv->resume();
      		 	//Serial.println(message.value);
      		 	return(message.value);
  			 	break;
  			 }
  			 delay(timeIntervalRead);
  		}
  			return(0);

      }

      unsigned long IRStation::ReadAddressedData(byte trialnumber ){

      	unsigned long tmp_1,tmp_2,tmp_3,tmp_4;
      	

      	for(int kk = 0 ; kk < trialnumber; kk++){
      		//Serial.println("first:");
      		tmp_1 = ReadIRData();
      		delay(timeIntervalRead);
      		if(tmp_1 == HeaderId){
      			delay(timeIntervalRead);
      			//Serial.println("second:");
      			tmp_2 = ReadIRData();
      			if(tmp_2 == _Address || tmp_2 == 0){
      				delay(timeIntervalRead);
      				tmp_3 = ReadIRData();
      				delay(timeIntervalRead);
      				tmp_4 = ReadIRData();
      				if(tmp_4 == (tmp_1 - tmp_2 - tmp_3))return(tmp_3);
      			}else{
      				delay(timeIntervalRead);
      			}
      		}else{
      			delay(timeIntervalRead);
      		}

      		return(0);


      }

  }

  #endif