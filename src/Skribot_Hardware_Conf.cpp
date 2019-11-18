#include "Skribot.h"

void Skribot::AddHardware(char *tag){
	switch(tag[0]){
		case 'M':
			switch(tag[1]){
				case '1':
					Add_Mono_LED_matrix(SPI_PORT_1);
				break;
				case '2':
					Add_Mono_LED_matrix(SPI_PORT_2);
				break;
			}
		break;
		case 'P':
			switch(tag[1]){
				case '1':
					pinMode(SKRIBRAIN_ANALOG_PIN_1,INPUT);
				break;
				case '2':
					pinMode(SKRIBRAIN_ANALOG_PIN_2,INPUT);
				break;
				case '3':
					pinMode(SKRIBRAIN_ANALOG_PIN_3,INPUT);
				break;
				case '4':
					pinMode(SKRIBRAIN_ANALOG_PIN_3,INPUT);
				break;
				case '5':
					pinMode(SKRIBRAIN_ANALOG_PIN_3,INPUT);
				break;	
			}
		break;
		case 'R':
			switch(tag[1]){
				
			}
		break;
	}
}

void Skribot::ClearHardware(){

}
