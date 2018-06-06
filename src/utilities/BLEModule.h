#ifndef BLE_MOD_H
#define BLE_MOD_H
#include "Arduino.h"
#include "RN4020.h"
#define EDU_BT_STATE_PIN 3
	enum moduleType {HM_10 = 0,RN4020 = 1};

	class BLEModule
{
public:
	BLEModule(moduleType type);
	char BLE_read();                                                        
    void BLE_write(char *msg);
    bool BLE_checkConnection();
    int  BLE_dataAvailable();
    void BLE_changeName(char name[],bool userConncection = true);
    void BLE_Setup();
    void BLE_reset();

private:
	moduleType	_type;

};

#endif