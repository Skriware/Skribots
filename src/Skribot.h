#ifndef SKRIBOT_H
#define SKRIBOT_H

#define DEBUG_MODE
//#define DEBUG_MODE_1


#include "Arduino.h"
#ifndef _VARIANT_BBC_MICROBIT_
#include <EEPROM.h>
#include <utilities/Claw.h>
#include <utilities/Scope.h> 
#include <utilities/Adafruit_NeoPixel.h>
#include <utilities/RobotLED.h>
#include <utilities/RGB_LED_Matrix.h>
#include <utilities/IRStation.h>
#include <utilities/BLEModule.h>
#include <utilities/SPIHandler.h>
#include <utilities/I2CHandler.h>
#include <utilities/Mono_LED_Matrix.h>
#include <utilities/Buzzer.h>
#include <utilities/Buttons.h>
#include <utilities/SmartRotorSystem.h>

#endif
#ifdef _VARIANT_BBC_MICROBIT_
#include <utilities/Adafruit_Microbit.h>
#endif

#include <utilities/DistSensor.h>
#include <utilities/LineSensor.h>
#include <utilities/Rotor.h>
#include <utilities/LightSensor.h>
#include <utilities/SoundDetector.h>
#include <utilities/PWM_Handler.h>
#include <utilities/StatusLED.h>
#include <utilities/Speaker.h>

#define _CAT(a, ...) a ## __VA_ARGS__
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_      1
#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)
#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))

#ifndef ESP_H

#define BOARD_VERSION 1

#define EDU_ROTOR_SPEED_PIN_R 6
#define EDU_ROTOR_DIR_PIN_R 7
#define EDU_ROTOR_SPEED_PIN_L 5
#define EDU_ROTOR_DIR_PIN_L 4
#define EDU_ECHO_PIN_1 10
#define EDU_ECHO_PIN_2 12
#define EDU_TRIG_PIN_1 9
#define EDU_TRIG_PIN_2 11
#define EDU_LINE_SENSOR_1 A1
#define EDU_LINE_SENSOR_2 A2
#define EDU_LINE_SENSOR_3 A3
#define EDU_LED_DATA_PIN 0 
#define EDU_LED_DATA_PIN_1 1
#define EDU_CLAW_PIN1 2
#define EDU_CLAW_PIN2 8
#define EDU_SHIELD
#define EDU_SHIELD_STATUS_LED_R_PIN A6
#define EDU_SHIELD_STATUS_LED_G_PIN A5
#define EDU_SHIELD_STATUS_LED_B_PIN A4
#define EDU_SHILED_POWER_READOUT_PIN A7

#define LINE_PIN_1 EDU_LINE_SENSOR_1
#define LINE_PIN_2 EDU_LINE_SENSOR_2
#define LINE_PIN_3 EDU_LINE_SENSOR_3

#define L1 A1
#define L2 A2
#define L3 A3

#else

#define BOARD_VERSION 1

#define SKRIBRAIN_MOTOR_L_DIR1_PIN 12 
#define SKRIBRAIN_MOTOR_L_DIR2_PIN 21
#define SKRIBRAIN_MOTOR_L_ENC_PIN 35
#define SKRIBRAIN_MOTOR_R_DIR1_PIN 23
#define SKRIBRAIN_MOTOR_R_DIR2_PIN 22
#define SKRIBRAIN_MOTOR_R_ENC_PIN 32
#define SKRIBRAIN_ECHO_PIN_1 5
#define SKRIBRAIN_ECHO_PIN_2 19
#define SKRIBRAIN_TRIG_PIN_1 17
#define SKRIBRAIN_TRIG_PIN_2 18
#define SKRIBRAIN_SERVO_PIN_1 13
#define SKRIBRAIN_SERVO_PIN_2 4
#define SKRIBRAIN_SERVO_PIN_3 16
#define SKRIBRAIN_LED_PIN_1 2
#define SKRIBRAIN_LED_PIN_2 15
#define SKRIBRAIN_ANALOG_PIN_1 36  
#define SKRIBRAIN_ANALOG_PIN_2 39 
#define SKRIBRAIN_ANALOG_PIN_3 34
#define SKRIBRAIN_STATUS_LED_PIN 14

#define D1_PORT 1
#define D2_PORT 2

#define SERVO_1 0
#define SERVO_2 1

#define L1_PORT 1
#define L2_PORT 2
#define L3_PORT 3

#define LINE_PIN_1 SKRIBRAIN_ANALOG_PIN_1
#define LINE_PIN_2 SKRIBRAIN_ANALOG_PIN_2
#define LINE_PIN_3 SKRIBRAIN_ANALOG_PIN_3

#endif

#define EEPROM_BOARD_VERSION_ADDR 5
#define EEPROM_SETTINGS_OVERRIDED_ADDR 6
#define EEPROM_LEFT_INVERT_ADDR 7
#define EEPROM_RIGHT_INVERT_ADDR 8
#define EEPROM_L1_BORDER_ADDR 9                         //16 bit values stored in two 8 bit addreses(ADDR and ADDR+1)
#define EEPROM_L2_BORDER_ADDR 11
#define EEPROM_L3_BORDER_ADDR 13
#define EEPROM_RIGHT_SCALE_ADDR 15
#define EEPROM_LEFT_SCALE_ADDR 16



#ifdef _VARIANT_BBC_MICROBIT_
#define SKRIBOT_MINI_SHILELD_MOTOR_1_DIR1_PIN 13 
#define SKRIBOT_MINI_SHILELD_MOTOR_1_DIR2_PIN 14
#define SKRIBOT_MINI_SHILELD_MOTOR_2_DIR1_PIN 15
#define SKRIBOT_MINI_SHILELD_MOTOR_2_DIR2_PIN 16
#define SKRIBOT_MINI_SHILELD_SENSOR_0 0
#define SKRIBOT_MINI_SHILELD_SENSOR_1 1
#define SKRIBOT_MINI_SHILELD_SENSOR_2 2
#define SKRIBOT_MINI_SHILELD_IR_IN 11
#define SKRIBOT_MINI_SHILELD_IR_OUT 9
#endif

#define LEFT 0
#define RIGHT 1


  class Skribot
 {
  public:
  	Skribot(String predef = "");
  	void AddDistSensor(int EchoPin,int TrigPin,String Name);
    void AddDistSensor(int EchoPin,int TrigPin,int id);
    void AddDistSensor(byte DIST_PORT);

    void AddLineSensor(int Pin, String Name); 
    void AddLineSensor(int Pin, int id);
    void AddDCRotor(int SpeedPin,int DirectionPin, String side);
    void AddLightSensor(int _pin,int id);
    void AddSpeaker(int _pin,int id);
    void AddI2CDevice(byte _SDA_PIN,byte _CLK_PIN,uint32_t freq = 100000);
    void AddSPIDevice(uint8_t MOSI_PIN,uint8_t MISO,uint8_t CLK_PIN,uint8_t CS_PIN);

     #ifndef _VARIANT_BBC_MICROBIT_ 
    void AddClaw(int ClawPin,int Arm_Pin, byte id = 0);
    void AddScope(int EchoPin,int Trigg,int ServoPin,String Name);
    void AddLED(int Pin,String name,byte N_LED = 1);
    void AddLED(int Pin, int id, byte N_LED  = 1);

    void Add_Mono_LED_matrix(byte SPI_PORT);
    void AddBuzzer(byte pin);
    void AddButton(byte pin,byte id);
    void ConfigureSPIHandler(byte SPI_PORT);
    bool EEPROM_EMPTY(int val);
    #endif
    
                                                                  //functions for element adding
    void AddDistSensor(String SHIELD_SLOT);
    void AddLED(String SHIELD_SLOT);
    void AddLineSensor(String SHIELD_SLOT);
    void AddDCRotor(String SHIELD_SLOT);
    void AddClaw();                                               //functions for elements adding when using Skriware shields
    void Set_Line_Sensor_Logic_Border(String id, int line, int noline);
    void wait_And_Check_BLE_Connection(int ms,int interval);
    void Calibrate_sensors_no_Line();
    void Calibrate_sensors_Line();
    void Move(char Direction,int ms);
    void FaceLeft(int ms = -1);
    void FaceRight(int ms = -1);
    void TurnLeft(int ms = -1);
    void TurnRight(int ms = -1);
    void MoveForward(int ms = -1);
    void MoveBack(int ms = -1);
    void RawRotorMove(int left,int right);
    void Set_Motor_Movment(byte motor_id, byte dir, byte speed,int time = -1);
    void Stop();   
    void Invert_Left_Rotors(bool inv = true);
    void Invert_Right_Rotors(bool inv = true);
    void Scale_Left_Rotors(byte scale);
    void Scale_Right_Rotors(byte scale);

    void SetSpeed_Raw(int speed);  
    void SetSpeed(int speed);                                                                    //functions for movements

    int ReadDistSensor(String id, int max = 150);
    int ReadDistSensor(int id, int max = 150);

    void Set_Line_Sensor_Logic_Border(int L1_border,int L2_border,int L3_border);
    void Configure_Connections(String predef="");

                                                                                                //distance sensor readout
    int ReadLineSensor(String name);
    int ReadLineSensor(int id);
    int ReadLineSensorData(int id);
    int ReadLineSensorData(String id);
                                                                                              // line sensor readout
    bool ConfigureBoardEEPROM();
    bool Check_Board_Version();
    int  Read_EEPROM_INT(byte addr);
    void Write_EEPROM_INT(byte addr,int val);



    void CloseClaw(byte id = 0);
    void OpenClaw(byte id  = 0);
    void Pick_Up(byte id = 0);
    void Put_Down(byte id = 0);                                                                //Claw functins
    
    void TurnLEDOn(int R,int G, int B,String name,byte N_LED =1);
    void TurnLEDOff(String name,byte N_LED =1); 
    void TurnLEDOn(int R,int G, int B,int _id = -69,byte N_LED = 1);
    void TurnLEDOff(int _id = -69,byte N_LED = 1);
    void SetLEDColor(int color_id);                                                            // LED functions

    int  LightSensor_Raw(int id);
    bool LightSensor_Dark(int id);
    bool LightSensor_Bright(int id);
                                                                                               //Light Sensor Functions

    #ifndef _VARIANT_BBC_MICROBIT_
    void SetScopeAngle(String id, int deg);  
    int  GetScopeDistance(String id);                                                         //Scope functions
    #endif
                                              //BLE FUCKTIONS
    char BLE_read();                                                        
    void BLE_write(char *msg);
    bool BLE_checkConnection();
    int  BLE_dataAvailable();
    void BLE_changeName(char name[],bool userConncection = true);
    void BLE_Setup();
    void BLE_reset();
    void BLE_Set_Module(moduleType type);
    void BLE_Flush();
    void BLE_Flush_Line();
    void sendNameInfo();
    bool ProgramENDRepotred();
    #ifdef ESP_H
    void SendMessage(int info);
    void SendMessage(char *info);

    void SendMessageLine(int info);
    void SendMessageLine(char *info);
    #endif

    void CONBRK();
    void IgnoreCONBRK();
    
    int BaterryCheck();
    byte ReadBattery();

    void EnterConfigMode();
    void ExitConfigMode();

    void AddHardware(char *tag);
    void ClearHardware();
 // private:
  DistSensor *DistSensors[2] = {NULL};
  LineSensor *LineSensors[2] = {NULL};
  Rotor *LeftDCRotors[2] = {NULL};
  Rotor *RightDCRotors[2] = {NULL};
  LightSensor *LightSensors[5] = {NULL};
  SmartRotor *leftSmartRotor = nullptr;
  SmartRotor *rightSmartRotor = nullptr;
  SmartRotorSystem *smartRotor = nullptr;
  bool using_BLE_Connection,
       connection_Break_Reported,
       program_End_Reported,
       stausLEDused,
       high_power_usage,
       claw_closed,
       config_mode,
       user_config,
       Remote_block_used,
       ignore_connection_break;
  long claw_closed_time;
  moduleType BLE_MODULE_TYPE;
  StatusLED *status;
  SPIHandler *SPIcomm[2];
  I2CHandler *I2Ccomm[2];
  byte Board_type = 0;

  #ifndef _VARIANT_BBC_MICROBIT_
  RobotLED *LEDs[5] = {NULL};
  Claw *Claws[2] = {NULL};
  Scope *Scopes[3] = {NULL};
  RGB_LED_Matrix *RGB_Matrix[3] = {NULL};
  BLEModule *BTmodule;
  Mono_LED_Matrix *LED_Matrixes[2] = {NULL};
  Buzzer *Buzzers[5];
  #endif
  byte NDistSensors,NLEDs,NLineSensors,NScopes,NLeftDCRotors,NRightDCRotors,NClaws,NLightSensors;           //counters
  int DCSpeed = 0;
  
  #ifdef _VARIANT_BBC_MICROBIT_
  Adafruit_Microbit_Matrix ledMatrix;
  Adafruit_Microbit_BLESerial BTLESerial;
  #endif

 };

 #endif
