#ifndef RN4020_FUNCT
#define RN4020_FUNCT
#ifndef ESP_H && _VARIANT_BBC_MICROBIT_
#include "Arduino.h"


	struct RN4020_info{
		char MAC[12];
		bool connected;
	};


	char RN4020_read();     

	RN4020_info RN4020_getInfo();                                                   
    void RN4020_write(char *msg);
    bool RN4020_checkConnection();
    int  RN4020_dataAvailable();
    void RN4020_changeName(char name[],bool userConncection = true);
    void RN4020_UARTwrite(char *str, int delayTime = 50);
    void RN4020_Setup();
    void RN4020_reset();
    int cti(char x);
    void incrementRXbuffIterator_beg();
    void incrementRXbuffIterator_deg();
	byte substractBufforIterators();
	char* asciiToHexString(char ascii);
    void serialFlush();

#endif
#endif