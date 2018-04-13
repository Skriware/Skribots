#ifndef IRSTATION_H
#define IRSTATION_H
#include <utilities/IR/IRremote.h>
  class IRStation
 {
  public:

      IRStation(int SendPin,int RecvPin,int Address);

      bool SendWithConfirmation(int TargetAddress,unsigned long data, byte trialnumber = 20);

      void Send(int TargetAddress,unsigned long data);

      unsigned long ReadIRData(byte trialnumber = 20);

      unsigned long ReadAddressedData(byte trialnumber = 20);

      IRrecv *irrecv;

      IRsend *irsend;

      decode_results message;

      
      
  private:

    int _Address;
    int _SendPin;
    const int HeaderId            = 69;
    const int confirmationId      = 13;
    const int timeIntervalRead    = 20;
    const int timeIntervalWrite   = 40;

 };

 #endif