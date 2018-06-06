#ifndef RN4020_FUNCT
#define RN4020_FUNCT
#include "Arduino.h"

	char RN4020_read();                                                        
    void RN4020_write(char *msg);
    bool RN4020_checkConnection();
    int  RN4020_dataAvailable();
    void RN4020_changeName(char name[],bool userConncection = true);
    void RN4020_Setup();
    void RN4020_reset();

#endif