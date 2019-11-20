#include "Skribot.h"
#define DEBUG_MODE_H
void Skribot::AddHardware(char *tag){
	switch(tag[0]){
		case 'M':
		#ifdef DEBUG_MODE_H
			Serial.println("MATRIX");
		#endif
			switch(tag[1]){
				case '1':
					Add_Mono_LED_matrix(SPI_PORT_1);
				break;
				case '2':
					Add_Mono_LED_matrix(SPI_PORT_2);
				break;
				default:
				break;
			}
		break;
		case 'P':
		#ifdef DEBUG_MODE_H
			Serial.println("BUTTON");
		#endif
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
				default:
				break;	
			}
		break;
		case 'R':
		#ifdef DEBUG_MODE_H
			Serial.println("MOTOR");
			Serial.println(tag[1]);
		#endif
			switch(tag[1]){
				case '1':
					AddDCRotor(SKRIBRAIN_MOTOR_L_DIR2_PIN,SKRIBRAIN_MOTOR_L_DIR1_PIN,"Left");
				break;
				case '2':
          			AddDCRotor(SKRIBRAIN_MOTOR_R_DIR2_PIN,SKRIBRAIN_MOTOR_R_DIR1_PIN,"Right");
				break;
				default:
				break;
			}
		break;
		case 'D':
		#ifdef DEBUG_MODE_H
			Serial.println("DISTANCE");
		#endif
			switch(tag[1]){
				case '1':
					AddDistSensor(SKRIBRAIN_ECHO_PIN_1,SKRIBRAIN_TRIG_PIN_1,1);
				break;
				case '2':
	          		AddDistSensor(SKRIBRAIN_ECHO_PIN_2,SKRIBRAIN_TRIG_PIN_2,2);
				break;
				default:
				break;
				}
		break;
		case 'B':
		#ifdef DEBUG_MODE_H
			Serial.println("BUZZER");
		#endif
			switch(tag[1]){
				case '1':
					AddBuzzer(SERVO_1);
				break;
				case '2':
					AddBuzzer(SERVO_2);
				break;
				case '3':
					AddBuzzer(SERVO_2);
				break;
				case '4':
					AddBuzzer(SERVO_2);
				break;
				case '5':
					AddBuzzer(SERVO_2);
				break;
				default:
				break;	
			}
		break;


	}
}

void Skribot::ClearHardware(){
	#ifdef DEBUG_MODE_H
		Serial.println("CLEAR HDW");
	#endif
	for(byte tt = 0; tt < 2; tt++){
		Serial.print("A");
		delete DistSensors[tt];
		Serial.print("B");
		delete LED_Matrixes[tt];
		Serial.print("C");
		delete LeftDCRotors[tt];
		Serial.print("D");
		delete RightDCRotors[tt];
		Serial.print("E");
	}
	for(byte rr = 0;rr<5;rr++){
		delete Buzzers[rr];
	}
	for(byte tt = 0; tt < 2; tt++){
      DistSensors[tt]=NULL;
      LED_Matrixes[tt]=NULL;
      LeftDCRotors[tt]=NULL;
      RightDCRotors[tt]=NULL;
    }
    for(byte rr = 0;rr<5;rr++){
      Buzzers[rr]=NULL;
    }
	NDistSensors = 0;
	NLeftDCRotors = 0;
	NRightDCRotors = 0;
	clearPWM();

}
