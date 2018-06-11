	#include "RN4020.h"

	
	void serialFlush(){
		delay(30);
  		while(Serial3.available() > 0) {
    		char t = Serial3.read();
  		}
	}   

	char RN4020_read(){
		return("B");

	}                                                        
    void RN4020_write(char *msg){

    }
    bool RN4020_checkConnection(){

    	RN4020_info info = RN4020_getInfo();
    	return(info.connected);
    }
    int  RN4020_dataAvailable(){
    	return(7);
    }

    RN4020_info RN4020_getInfo(){

    	RN4020_info rn4020_info;
    	char tmp[150];
    	char *mac[12];
    	bool conn;
    	
    	RN4020_UARTwrite("D",1);
    	
    	byte kk = 0;
    	
    	while(Serial3.available() || kk < 70){
    		if(Serial3.available()){
    		tmp[kk] = Serial3.read(); 
    		kk++;
    		}
    	}

    	byte thingsRead = 0;
    	for(int zz = 0; zz < kk ; zz++){
    		if(thingsRead == 0 && tmp[zz] == '='){
    			for(int yy = 1; yy < 13;yy++){
    				mac[yy-1]=tmp[zz+yy];
    			}
    			thingsRead++;
    		}
    		else if(thingsRead == 1 && tmp[zz] == '='){
    			thingsRead++;
    		}
    		else if(thingsRead == 2 && tmp[zz] == '='){
    			thingsRead++;
    		}else if(thingsRead == 3 && tmp[zz] == '='){
    			Serial.println(tmp[zz+1]);
    		 if(tmp[zz+1] == 'n' && tmp[zz+2] == 'o'){
    		 	conn = false;
    		 }else{
    		 	conn = true;
    		 }
    		 break;
    		}
    	}
    	serialFlush();
    	for(int ii = 0; ii < 12; ii++)rn4020_info.MAC[ii] = mac[ii];
    	rn4020_info.connected = conn;
    	return(rn4020_info);
    }   


    void RN4020_changeName(char name[],bool userConncection){
       char tmpmess[32] = {' '};
       sprintf(tmpmess,"SN,%s",name);
       RN4020_UARTwrite(tmpmess);

       RN4020_reset();
    }
    void RN4020_Setup(){

    	Serial3.begin(115200);

    	delay(500);

    	RN4020_UARTwrite("SF,1"); // Factory Reset
    								
		RN4020_UARTwrite("SS,00000001"); // Enable private service
									
		RN4020_UARTwrite("SR,20000000"); // Set as Peripheral
									
		RN4020_UARTwrite("PZ"); // Clean private Service 
									
		RN4020_UARTwrite("PS,123456789012345678901234567890FF"); // Set private service UUID 
									
																								    // Set private
		RN4020_UARTwrite("PC,12345678901234567890123456789011,12,02");			
															// characteristic to be readable, notifiable and 2 bytes
																									// in length
		RN4020_UARTwrite("PC,12345678901234567890123456789022,02,02");
									 // Set private
												  // characteristic to be readable and 2 bytes in length
		RN4020_info info = RN4020_getInfo();
		char BLEName[24];
		sprintf(BLEName,"SKRIBOT_%c%c%c",info.MAC[9],info.MAC[10],info.MAC[11]);
		RN4020_changeName(BLEName); 

    }
    void RN4020_reset(){
    	RN4020_UARTwrite("R,1",2000); // Reboot

    }

    void RN4020_UARTwrite(char *str,int delaytime){
    	serialFlush();
    	Serial3.println(str); 
    	delay(delaytime);

    }

