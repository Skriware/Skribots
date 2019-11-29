#include "PWM_Handler.h"

  byte used_PWM_channels = 0;
  PWM_Channel PWM_Channels[MAX_PWM_CHANNELS];
  bool PWM_overload = false;


  void PWM_Write(byte _PWMPin,int value){
      for(byte ii = 0; ii < MAX_PWM_CHANNELS;ii++){
        if(PWM_Channels[ii].pwmPin == _PWMPin){
        #ifdef ESP_H
          ledcWrite(PWM_Channels[ii].pwmChannel,value);
        #else 
          analogWrite(PWM_Channels[ii].pwmPin,value);
        #endif
        break;
        }
      }
  }

  int SetNewPWMChannel(byte _PWMPin){
    PWM_Channel newChannelToUse;
    if(used_PWM_channels+1 > MAX_PWM_CHANNELS){
      PWM_overload = true;
      return -1;
    }else{
          newChannelToUse.pwmPin = _PWMPin;
          newChannelToUse.pwmChannel = used_PWM_channels;
          PWM_Channels[used_PWM_channels] = newChannelToUse;
          used_PWM_channels++;
        #ifdef ESP_H
          ledcSetup(newChannelToUse.pwmChannel, PWM_FREQ, PWM_RESOLUTION);
          ledcAttachPin(newChannelToUse.pwmPin, newChannelToUse.pwmChannel); 
        #endif
        #if defined(_VARIANT_BBC_MICROBIT_) || defined(ARDUINO_AVR_MEGA2560)
          pinMode(_PWMPin, OUTPUT);
        #endif
      return used_PWM_channels - 1;
    }

  }

  bool PWM_overloaded(){
    return(PWM_overload);
  }

  void clearPWM(){
    for(byte tt = 0; tt < used_PWM_channels;tt++){
      ledcDetachPin(PWM_Channels[tt].pwmPin);
    }
    used_PWM_channels = 0;
  }

bool PWM_defined(byte pin)
{
  for (byte i = 0; i < used_PWM_channels; i++)
  {
    if (PWM_Channels[i].pwmPin == pin)
      return true;
  }
  return false;
}