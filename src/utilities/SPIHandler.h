#ifndef SPIHANDLER_H
#define SPIHANDLER_H
#include "Arduino.h"
#include "SPI.h"

class SPIHandler
{
public:
	  #ifdef ESP_H
	  SPIHandler(uint8_t MOSI_PIN,uint8_t MISO,uint8_t CLK_PIN,uint8_t CS_PIN);
	  #else
	  SPIHandler(uint8_t CS_PIN);
	  #endif
	  ~SPIHandler();
	  void set_SPI_Settings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode);
	  void set_SPI_bit_format(uint8_t nbit);

	  uint8_t TransferAndReciveByte_8(uint8_t data);
	  uint16_t TransferAndReciveByte_16(uint16_t data);
	  uint32_t TransferAndReciveByte_32(uint32_t data);

	  uint8_t  SPITransfer(uint8_t *msg);
	  uint32_t SPI_get_output(uint8_t ii);
	  void SPI_end();
	  static uint8_t used_spi_bus;
private:
	#ifdef ESP_H
	uint8_t MOSI_PIN;
	uint8_t MISO_PIN;
	uint8_t CLK_PIN;
	#endif
	uint8_t CS_PIN;
	const uint8_t buffer_Size = 16;
	uint32_t _clock = 5000000;
	#ifdef ESP_H
	uint8_t _bitOrder = SPI_MSBFIRST;
	#else
	uint8_t _bitOrder = MSBFIRST;
	#endif
	uint8_t _dataMode = SPI_MODE0;
	uint8_t bit_format;
	SPIClass *_spi;
	uint32_t output[16];
};


#endif