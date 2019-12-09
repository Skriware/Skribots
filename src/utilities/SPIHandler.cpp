#include "SPIHandler.h"

  uint8_t SPIHandler::used_spi_bus = 0;

  #ifdef ESP_H
    SPIHandler::SPIHandler(byte MOSI_PIN,byte MISO,byte CLK_PIN,byte _CS_PIN){
      if(used_spi_bus == 0){
      _spi = new SPIClass(HSPI);
      used_spi_bus++;
      }else if(used_spi_bus == 1){
      _spi = new SPIClass(VSPI);
      used_spi_bus++;	
      }else{
        #ifdef DEBUG_MODE
        Serial.println("No more free SPI bus!");
        #endif
        return;
      }
      _spi->begin(CLK_PIN,MISO_PIN,MOSI_PIN);
      CS_PIN = _CS_PIN;
      pinMode(CS_PIN,OUTPUT);
      digitalWrite(CS_PIN,HIGH);
    }

    SPIHandler::SPIHandler(byte _SPI_PORT){
    if(used_spi_bus == 0){
          _spi = new SPIClass(HSPI);
          used_spi_bus++;
        }else if(used_spi_bus == 1){
          _spi = new SPIClass(VSPI);
          used_spi_bus++;	
        }else{
          #ifdef DEBUG_MODE
          Serial.println("No more free SPI bus!");
          #endif
        return;
        }
    if(_SPI_PORT == SPI_PORT_1){
        SPI_PORT = _SPI_PORT;
        _spi->begin(SPI_PORT_1_CLK_PIN,SPI_PORT_1_MISO_PIN,SPI_PORT_1_MOSI_PIN);
        CS_PIN = SPI_PORT_1_CS_PIN;
      }else if(_SPI_PORT == SPI_PORT_2){
        SPI_PORT = _SPI_PORT;
        _spi->begin(SPI_PORT_2_CLK_PIN,SPI_PORT_2_MISO_PIN,SPI_PORT_2_MOSI_PIN);
        CS_PIN = SPI_PORT_2_CS_PIN;
      }else{
        SPI_PORT = 2;
      }  	
      pinMode(CS_PIN,OUTPUT);
        digitalWrite(CS_PIN,HIGH);
    }
  #else
    SPIHandler::SPIHandler(byte _CS_PIN){
      CS_PIN = _CS_PIN;
      pinMode(CS_PIN,OUTPUT);
      digitalWrite(CS_PIN,HIGH);
      _spi = new SPIClass();
      _spi->begin();
    }
  #endif
    SPIHandler::~SPIHandler(){
      _spi->end();
      delete _spi;
      _spi = nullptr;
      used_spi_bus--;
    }
    void SPIHandler::set_SPI_Settings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode){
      _clock = clock;
      _bitOrder = bitOrder;
      _dataMode = dataMode;
    }
    void SPIHandler::set_SPI_bit_format(byte nbit){
      bit_format = nbit;
    }
    uint8_t SPIHandler::TransferAndReciveByte_8(uint8_t data){
      digitalWrite(CS_PIN,LOW);
       _spi->beginTransaction(SPISettings(_clock,_bitOrder,_dataMode));  
       uint8_t out = _spi->transfer(data);
       digitalWrite(CS_PIN,HIGH);
       _spi->endTransaction();
       return(out);
    }
    
    uint16_t SPIHandler::TransferAndReciveByte_16(uint16_t data){
      digitalWrite(CS_PIN,LOW);
       _spi->beginTransaction(SPISettings(_clock,_bitOrder,_dataMode));  
       uint16_t out = _spi->transfer16(data);
       digitalWrite(CS_PIN,HIGH);
       _spi->endTransaction();
       return(out);
    }
    
    #ifdef ESP_H
    uint32_t SPIHandler::TransferAndReciveByte_32(uint32_t data){
      digitalWrite(CS_PIN,LOW);
       _spi->beginTransaction(SPISettings(_clock,_bitOrder,_dataMode));  
       uint32_t out = _spi->transfer32(data);
       digitalWrite(CS_PIN,HIGH);
       _spi->endTransaction();
       return(out);
    }
    #endif
    
    uint8_t  SPIHandler::SPITransfer(uint8_t *msg){
      uint8_t Nsend = msg[0] & B00001111;              //number of bytes to send
      uint8_t Nrec  = (msg[0]>>4) & B00001111;
      if(bit_format == 8){
          for(byte yy = 1; yy < Nsend+1;yy++){
            TransferAndReciveByte_8(msg[yy]);
          }
          for(byte zz = 0; zz<Nrec;zz++){
            output[zz] = TransferAndReciveByte_8(0);             //receiving data 
          }
      }else if(bit_format == 16){
            uint16_t msg_16[Nsend];
            uint8_t zz = 0;
          for(uint8_t jj = 0; jj<Nsend;jj++){
           msg_16[jj] = uint16_t(msg[zz+1] << 8) | uint16_t(msg[zz+2]);
           zz+=2;
          }

          for(byte yy = 0; yy < Nsend;yy++){
            TransferAndReciveByte_16(msg_16[yy]);
            }
            for(byte zz = 0; zz<Nrec;zz++){
            output[zz] = TransferAndReciveByte_16(0);             //receiving data 
            }
      }
      #ifdef ESP_H
      else if (bit_format == 32){

      }
      #endif
    } 
    
    
    uint32_t SPIHandler::SPI_get_output(byte ii){
      return(output[ii]);
    }
