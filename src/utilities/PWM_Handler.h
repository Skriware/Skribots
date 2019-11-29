#ifndef PWM_HANDLE_H
#define PWM_HANDLE_H
#include "Arduino.h"
#ifdef ESP_H
#include "esp32-hal-ledc.h"
#define MAX_PWM_CHANNELS 16
#define PWM_FREQ 490
#define PWM_RESOLUTION 8 //in bits
#endif
#ifdef _VARIANT_BBC_MICROBIT_
#define MAX_PWM_CHANNELS 3
#endif
#ifdef ARDUINO_AVR_MEGA2560
#define MAX_PWM_CHANNELS 5
#endif


  struct PWM_Channel{
    byte pwmPin;
    byte pwmChannel;
  };
  void PWM_Write(byte PWMPin,int value);
  int SetNewPWMChannel(byte PWMPin);
  bool PWM_overloaded();
  void clearPWM();
  bool PWM_defined(byte pin);
#endif