#include "Skribot.h"
//#define DEBUG_MODE_H
#define SMART_ROTOR
#ifdef DEBUG_MODE_H
  #define DEBUG_PRINT(msg) Serial.println(msg)
#else
  #define DEBUG_PRINT(msg)
#endif

#define CASE_MATRIX 'M'
#define CASE_BUTTON 'P'
#define CASE_SROTOR 'R'
#define CASE_ROTOR  'Q'
#define CASE_DISTANCE 'D'
#define CASE_CLAW 'C'
#define CASE_LINE 'L'
#define CASE_LED  'W'
#define CASE_BUZZER 'B'


void Skribot::AddHardware(char *tag){
  switch(tag[0]){
    case CASE_MATRIX:
      DEBUG_PRINT("MATRIX");
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
    case CASE_BUTTON:
      DEBUG_PRINT("BUTTON");
      switch(tag[1]){
        case '1':
          pinMode(SKRIBRAIN_ANALOG_PIN_1,INPUT);
          AddLineSensor(LINE_PIN_1, 1);
        break;
        case '2':
          pinMode(SKRIBRAIN_ANALOG_PIN_2,INPUT);
          AddLineSensor(LINE_PIN_2, 2);
        break;
        case '3':
          pinMode(SKRIBRAIN_ANALOG_PIN_3,INPUT);
          AddLineSensor(LINE_PIN_3, 3);
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
    case CASE_SROTOR:
    #ifdef SMART_ROTOR
      DEBUG_PRINT("SMOTOR");
      DEBUG_PRINT(tag[1]);
      switch(tag[1])
      {
        case '1':
          DEBUG_PRINT("creating left smart rotor");
          leftSmartRotor = new SmartRotor(
            SKRIBRAIN_MOTOR_L_DIR1_PIN,
            SKRIBRAIN_MOTOR_L_DIR2_PIN,
            SKRIBRAIN_MOTOR_L_ENC_PIN
          );
          leftSmartRotor->begin();
          break;

        case '2':
          DEBUG_PRINT("creating right smart rotor");
          rightSmartRotor = new SmartRotor(
            SKRIBRAIN_MOTOR_R_DIR1_PIN,
            SKRIBRAIN_MOTOR_R_DIR2_PIN,
            SKRIBRAIN_MOTOR_R_ENC_PIN
          );
          rightSmartRotor->begin();
          break;
          
        default:
          break;
      }

      if (
        leftSmartRotor != nullptr &&
        rightSmartRotor != nullptr &&
        smartRotor == nullptr
      ) {
        DEBUG_PRINT("creating smart rotor system");
        smartRotor = new SmartRotorSystem(leftSmartRotor, rightSmartRotor);
        smartRotor->begin();
      } 
    #endif
      break;

      case(CASE_ROTOR):
      DEBUG_PRINT("ROTOR");
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
    case CASE_DISTANCE:
      DEBUG_PRINT("DISTANCE");
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
    case CASE_BUZZER:
      DEBUG_PRINT("BUZZER");
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
    case CASE_CLAW:
      switch(tag[1]){
        case '0':
          DEBUG_PRINT("CLAW");
          AddClaw();
        break;
      }
    break;
    case CASE_LINE:
    DEBUG_PRINT("LINE");
    switch(tag[1]){
      case '1':
        AddLineSensor(LINE_PIN_1, 1);
      break;
      case '2':
        AddLineSensor(LINE_PIN_2, 2);
      break;
      case '3':
        AddLineSensor(LINE_PIN_3, 3);
      break;
    }
    break;
    case CASE_LED:
    DEBUG_PRINT("LED");
      switch(tag[1]){
        case '1':
          AddLED(SKRIBRAIN_LED_PIN_2,1);
        break;
        case '2':
          AddLED(SKRIBRAIN_LED_PIN_1,0);
        break;
      }
    break;
  }
}

void Skribot::ClearHardware(){
  DEBUG_PRINT("CLEAR HDW");
  for(byte tt = 0; tt < 2; tt++){
    if (DistSensors[tt] !=NULL)delete DistSensors[tt];
    if (LED_Matrixes[tt] !=NULL)delete LED_Matrixes[tt];
    if (LeftDCRotors[tt] !=NULL)delete LeftDCRotors[tt];
    if (RightDCRotors[tt] !=NULL)delete RightDCRotors[tt];
    if (LineSensors[tt] !=NULL)delete LineSensors[tt];
    if (Claws[tt] != NULL)delete Claws[tt];
    if (LEDs[tt] != NULL)delete LEDs[tt];
  }
  if (smartRotor != nullptr)
  {
    DEBUG_PRINT("deleting smart rotor system");
    delete smartRotor;
    smartRotor = nullptr;
    leftSmartRotor = nullptr;
    rightSmartRotor = nullptr;
  }

  if (leftSmartRotor != nullptr)
  {
    DEBUG_PRINT("deleting left smart rotor");
    delete leftSmartRotor;
    leftSmartRotor = nullptr;
  }

  if (rightSmartRotor != nullptr)
  {
    DEBUG_PRINT("deleting right smart rotor");
    delete rightSmartRotor;
    rightSmartRotor = nullptr;
  }

  for(byte rr = 0;rr<5;rr++){
    delete Buzzers[rr];
  }
  for(byte tt = 0; tt < 2; tt++){
      DistSensors[tt]=NULL;
      LED_Matrixes[tt]=NULL;
      LeftDCRotors[tt]=NULL;
      RightDCRotors[tt]=NULL;
      LineSensors[tt]=NULL;
      Claws[tt] = NULL;
      LEDs[tt] =NULL;
    }
    for(byte rr = 0;rr<5;rr++){
      Buzzers[rr]=NULL;
    }
  NDistSensors = 0;
  NLeftDCRotors = 0;
  NRightDCRotors = 0;
  NLineSensors = 0;
  NClaws = 0;
  NLEDs = 0;
  clearPWM();

  for (int i = 0; i < 2; i++)
  {
    delete SPIcomm[i];
    SPIcomm[i] = nullptr;
  }
  Serial.println("DELETED");
}

#undef DEBUG_PRINT
