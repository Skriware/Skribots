#include "I2CHandler.h"
	  #ifdef ESP_H
	uint8_t I2CHandler::used_i2c_bus = 0;
	  I2CHandler::I2CHandler(byte _SDA_PIN,byte _CLK_PIN,uint32_t freq){
	  if(used_i2c_bus == 0){
	  	i2c = new TwoWire(0);
	  	used_i2c_bus++;
	  	}else if(used_i2c_bus == 1){
	  	i2c = new TwoWire(1);
	  	used_i2c_bus++;	
	  	}else{
	  		#ifdef DEBUG_MODE
	  		Serial.println("No more free I2C bus!");
	  		#endif
	  		return;
	  	}
	  i2c->begin(_SDA_PIN,_CLK_PIN,freq);
	  SDA_PIN = _SDA_PIN;
	  CLK_PIN = _CLK_PIN;
	  clock = freq; 
	  connected_devices = 0;
	  }
	  #else
	  I2CHandler::I2CHandler(){
	  i2c = new TwoWire();
	  i2c->begin();
	  }
	  #endif
	  I2CHandler::~I2CHandler(){
	  	//i2c->end();
	  	delete i2c;
	  }

	  bool I2CHandler::I2Cscan(uint8_t address_to_find){
	  	bool address_found =  false;
	  	byte error;
	  for(byte tmpaddress  = 1; tmpaddress < 128; tmpaddress++){  //I2C scan
        i2c->beginTransmission(tmpaddress);
        error = i2c->endTransmission(true);
      if (error == 0){
      	#ifdef DEBUG_MODE
        Serial.print("I2C device found at address 0x");
        if (tmpaddress<16)
        Serial.print("0");
        Serial.print(tmpaddress,HEX);
        Serial.println("  !");
        #endif
        if (tmpaddress == address_to_find) address_found = true;
        if (connected_devices < 10){
          addresses[connected_devices] = tmpaddress;
          connected_devices++;
        }else{
        	#ifdef DEBUG_MODE
        		Serial.println("To many I2C modules for I2CHandler");
        	#endif
        }
      }else if (error==4){
      		#ifdef DEBUG_MODE
            Serial.print("Unknown error at address 0x");
            if (tmpaddress<16)
            Serial.print("0");
            Serial.println(tmpaddress,HEX);
            #endif
      } 
      #ifdef DEBUG_MODE
      if(connected_devices == 0)Serial.println("No modules found."); 
      #endif  
    }
    return(address_found);
	 }
 
 	bool I2CHandler::I2CSend(byte in,byte addr){
          i2c->beginTransmission(addr);
          i2c->write(in);
          if(i2c->endTransmission() !=0){
          	return(true);
          }else{
          	return(false);
          }
    }
    byte I2CHandler::I2CRecive(byte addr,byte size){
          byte out =0;
          i2c->requestFrom(addr,size);
          while(i2c->available()){ 
            out=i2c->read();        
          }
          return(out);
    }
	  bool I2CHandler::I2CTransfer(byte *msg,byte addr){
           for(byte p = 0; p < 15; p++)output_buffer[p] = 0;
              byte Nsend = msg[0] & B00001111;              //number of bytes to send
              byte Nrec  = (msg[0]>>4) & B00001111;         // nuber of bytes to recive
              byte output[Nrec];
              I2CSend(msg[0],addresses[addr]);           //transmit header
              I2CSend(msg[1],addresses[addr]);           //transfering command address
              for(byte yy = 1; yy < Nsend+1;yy++){
                if(!I2CSend(msg[yy+1],addresses[addr])){
                	return(false);
                }
              }
              for(byte zz = 0; zz<Nrec;zz++){
                output[zz] = I2CRecive(addresses[addr],1);             //receiving data 
              }
              for(byte pp = 0; pp < Nrec; pp++)output_buffer[pp] = output[pp];
              return(true);
    }
	  uint8_t I2CHandler::I2C_get_output(byte ii){
	  		return(output_buffer[ii]);
	  }
	  