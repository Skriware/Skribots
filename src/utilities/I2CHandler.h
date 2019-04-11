#ifndef I2CHANDLER_H
#define I2CHANDLER_H
#include "Arduino.h"
#include "Wire.h"
						
class I2CHandler
{
public:
	  #ifdef ESP_H
	  I2CHandler(byte _SDA_PIN,byte _CLK_PIN,uint32_t freq = 100000);
	  #else
	  I2CHandler();
	  #endif
	  ~I2CHandler();
	  bool I2Cscan(uint8_t address_to_find);
	  bool I2CSend(byte in,byte addr);
      byte I2CRecive(byte addr,byte size);
	  bool I2CTransfer(byte *msg,byte addr = 0);
	  uint8_t I2C_get_output(byte ii);
	  void I2C_end();
	  
private:
	#ifdef ESP_H
	byte SDA_PIN;
	byte CLK_PIN;
	static uint8_t used_i2c_bus ; 
	#endif
	TwoWire *i2c = NULL;
	uint32_t clock = 100000;
	uint8_t output_buffer[16];
	uint8_t addresses[10];
	byte connected_devices;
};

#endif