#include "PWM_Handler.h"

	byte used_PWM_channels = 0;
	PWM_Channel PWM_Channels[MAX_PWM_CHANNELS];
	bool PWM_overload = false;


	void PWM_Write(byte _PWMPin,int value){
			for(byte ii = 0; ii < MAX_PWM_CHANNELS;ii++){
				if(PWM_Channels[ii].pwmPin == _PWMPin){
				#ifdef ARDUINO_ARCH_ESP32
					ledcWrite(PWM_Channels[ii].pwmChannel,value);
				#else 
					analogWrite(PWM_Channels[ii].pwmPin,value);
				#endif
				break;
				}
			}
	}

	void SetNewPWMChannel(byte _PWMPin){

		PWM_Channel newChannelToUse;

		if(used_PWM_channels+1 > MAX_PWM_CHANNELS){
			PWM_overload = true;
		}else{
					newChannelToUse.pwmPin = _PWMPin;
					newChannelToUse.pwmChannel = used_PWM_channels;
					PWM_Channels[used_PWM_channels] = newChannelToUse;
					used_PWM_channels++;
				#ifdef ARDUINO_ARCH_ESP32
					ledcSetup(newChannelToUse.pwmChannel, PWM_FREQ, PWM_RESOLUTION);
					ledcAttachPin(newChannelToUse.pwmPin, newChannelToUse.pwmChannel); 
				#endif
				#ifdef _VARIANT_BBC_MICROBIT_ || ARDUINO_AVR_MEGA2560
					pinMode(pwmPin,OUTPUT);
				#endif
		}

	}

	bool PWM_overloaded(){
		return(PWM_overload);
	}




