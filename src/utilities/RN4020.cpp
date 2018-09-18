	#include "RN4020.h"
	#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
	#define BLERXBUFFER_SIZE 21
	char RXBLE_buffer[BLERXBUFFER_SIZE];
	byte RXBLE_buffer_iterator_end = 1;
	byte RXBLE_buffer_iterator_beg = 0;
	bool newdataArrived = false;
    bool connection = false;

	
	void serialFlush(){
		delay(30);
		if(Serial3.available()){
  		while(Serial3.available() > 0) {
    		char t = Serial3.read();
            delay(5);
    		if(t == 'W' && Serial3.read() == 'V'){newdataArrived = true;}
            if(t == 'C'){
                for(int uu = 0; uu < 8; uu++){
                    t = Serial3.read();
                }
                if(t == 'd'){
                    connection = true;
                }else if(t == 'o'){
                    connection = false;
                }
            }
    		delay(1);
  		}
  		}
	}   

	char RN4020_read(){
        if(BLERXBUFFER_SIZE - substractBufforIterators() > 0){
			incrementRXbuffIterator_beg();
            char tmp = RXBLE_buffer[RXBLE_buffer_iterator_beg];
			return(tmp);
		}

		return('Q');

	}                                                        
    void RN4020_write(char *msg){
        
    	char tmp[21];
    	sprintf(tmp,"%s\n",msg);
       Serial3.print("SUW,12345678901234567890123456789022,");
       for(int yy = 0; yy < 21 ; yy++){
       	if(tmp[yy] == '\n')break;
       	Serial3.print(int(tmp[yy]),HEX);
       }
       	Serial3.println();
       serialFlush();
       delay(10);
    }

    bool RN4020_checkConnection(){
        serialFlush();
    	return(connection);
    }

    void incrementRXbuffIterator_end(){
    	if(RXBLE_buffer_iterator_end == BLERXBUFFER_SIZE-1){
    		RXBLE_buffer_iterator_end = 0;
    	}else{
    		RXBLE_buffer_iterator_end++;
    	}
    }

      void incrementRXbuffIterator_beg(){
    	if(RXBLE_buffer_iterator_beg == BLERXBUFFER_SIZE-1){
    		RXBLE_buffer_iterator_beg = 0;
    	}else{
    		RXBLE_buffer_iterator_beg++;
    	}
    }

    byte substractBufforIterators(){
    	if(RXBLE_buffer_iterator_end < RXBLE_buffer_iterator_beg){
    		return(RXBLE_buffer_iterator_beg - RXBLE_buffer_iterator_end);
    	}else if(RXBLE_buffer_iterator_beg < RXBLE_buffer_iterator_end){
    		return(BLERXBUFFER_SIZE - RXBLE_buffer_iterator_end + RXBLE_buffer_iterator_beg);
    	}else{
    		return(0);
    	}
    }

    int cti(char x){
  		int y = x - '0';
 	 	return(y);
	}

    int  RN4020_dataAvailable(){
    			serialFlush();
    			if(newdataArrived){
    				RN4020_UARTwrite("SUR,12345678901234567890123456789011",10);		//Reading the characteristic
    				while(Serial3.available() && substractBufforIterators() >= 1){
    					char tmp1 = Serial3.read();
                        char tmp2 = Serial3.read();
                        if(tmp1 == '\n')break;
                        byte hex1 = int(tmp1);
    					byte hex2 = int(tmp2);
    					if(hex1 > 47 && hex1 < 58){
    						hex1 -= 48;
    					}else if(hex1 > 64 && hex1 < 71){
    						hex1 -= 55;
    					}
    					if(hex2 > 47 && hex2 < 58){
    						hex2 -= 48;
    					}else if(hex2 > 64 && hex2 < 71){
    						hex2 -= 55;
    					}
    					char ascii = 16*hex1+hex2;
                        if(hex1 == 13 && hex2 == 10) ascii = '\n';
    					RXBLE_buffer[RXBLE_buffer_iterator_end] = ascii;
    					incrementRXbuffIterator_end();
    					}
    				newdataArrived = false;
    				serialFlush();
    			 
    		}
    	
    		return(BLERXBUFFER_SIZE - substractBufforIterators()-1);
    }

    RN4020_info RN4020_getInfo(){

    	RN4020_info rn4020_info;
    	char tmp[150];
    	char *mac[12];
    	bool conn;
    	
    	RN4020_UARTwrite("D",1);
    	
    	byte kk = 0;
    	
    	while(Serial3.available() || kk < 70){		//70 - number of bytes after which we have all the information
    		if(Serial3.available()){
    		tmp[kk] = Serial3.read(); 
    		kk++;
    		delay(1);
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
		RN4020_UARTwrite("PC,12345678901234567890123456789011,04,20");			
															// characteristic to be readable, notifiable and 2 bytes
																									// in length
		RN4020_UARTwrite("PC,12345678901234567890123456789022,10,20");
									 // Set private
												  // characteristic to be readable and 2 bytes in length
		RN4020_info info = RN4020_getInfo();
		char BLEName[24];
		sprintf(BLEName,"SKRIBOT_%c%c%c",info.MAC[9],info.MAC[10],info.MAC[11]);
		RN4020_changeName(BLEName); 

    }
    void RN4020_reset(){
    	RN4020_UARTwrite("R,1",2000); // Reboot
    	serialFlush();

    }

    void RN4020_UARTwrite(char *str,int delaytime){
    	serialFlush();
    	Serial3.println(str); 
    	delay(delaytime);

    }

#endif