#ifndef SKRIBOT_H
#define SKRIBOT_H
#include "Arduino.h"
#ifndef _VARIANT_BBC_MICROBIT_
#include <EEPROM.h>
#include <utilities/ServoRotor.h>
#include <utilities/Claw.h>
#include <utilities/Scope.h> 
#include <utilities/Adafruit_NeoPixel.h>
#include <utilities/RobotLED.h>
#include <utilities/RGB_LED_Matrix.h>
#include <utilities/IRStation.h>
#include <utilities/BLEModule.h>
#endif
#include <utilities/DistSensor.h>
#include <utilities/LineSensor.h>
#include <utilities/Rotor.h>
#include <utilities/LightSensor.h>
#include <utilities/SoundDetector.h>
#ifdef _VARIANT_BBC_MICROBIT_
#include <utilities/Adafruit_Microbit.h>
#endif

#define _CAT(a, ...) a ## __VA_ARGS__
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_      1
#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)
#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))

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
#define EDU_LED_DATA_PIN 1
#define EDU_LED_DATA_PIN_1 0
#define EDU_CLAW_PIN1 2
#define EDU_CLAW_PIN2 8

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




  class Skribot
 {
  public:
  	Skribot(String predef = "");
  	void AddDistSensor(int EchoPin,int TrigPin,String Name);
    void AddDistSensor(int EchoPin,int TrigPin,int id);
    void AddLineSensor(int Pin, String Name); 
    void AddLineSensor(int Pin, int id);
    void AddDCRotor(int SpeedPin,int DirectionPin, String side);
    void AddLightSensor(int _pin,int id);

     #ifndef _VARIANT_BBC_MICROBIT_
    void AddClaw(int ClawPin,int Arm_Pin, byte id = 0);
    void AddScope(int EchoPin,int Trigg,int ServoPin,String Name);
    void AddLED(int Pin,String name);
    void AddLED(int Pin, int id);
    #endif
    
                                                                  //functions for element adding
    void AddDistSensor(String EDU_SHIELD_SLOT);
    void AddLED(String EDU_SHIELD_SLOT);
    void AddLineSensor(String EDU_SHIELD_SLOT);
    void AddDCRotor(String EDU_SHIELD_SLOT);
    void AddClaw();                                               //functions for elements adding when using Skriware Edu shield

    void Configure_Connections(String predef="");

    void wait_And_Check_BLE_Connection(int ms,int interval);

    void Move(char Direction,int ms);
    void FaceLeft(int ms = 200);
    void FaceRight(int ms = 200);
    void TurnLeft(int ms = 200);
    void TurnRight(int ms = 200);
    void MoveForward(int ms = -1);
    void MoveBack(int ms = -1);
    void RawRotorMove(int left,int right);
    void Stop();   

    void SetSpeed(int speed);                                                                    //functions for movements

    int ReadDistSensor(String id, int max = 150);
    int ReadDistSensor(int id, int max = 150);
                                                                                                //distance sensor readout
    int ReadLineSensor(String name);
    int ReadLineSensor(int id);
                                                                                              // line sensor readout
     
    void CloseClaw(byte id = 0);
    void OpenClaw(byte id  = 0);
    void Pick_Up(byte id = 0);
    void Put_Down(byte id = 0);                                                                //Claw functins
    
    void TurnLEDOn(int R,int G, int B,String name);
    void TurnLEDOff(String name); 
    void TurnLEDOn(int R,int G, int B,int _id = -69);
    void TurnLEDOff(int _id = -69);                                                            // LED functions

    int ReadLightRaw(int id);
    bool LightSensorDark(int id);
    bool LightSensorBright(int id);
                                                                                               //Light Sensor Functions

    #ifndef _VARIANT_BBC_MICROBIT_
    void SetScopeAngle(String id, int deg);  
    int  GetScopeDistance(String id);                                                         //Scope functions
    #endif

    char BLE_read();                                                        
    void BLE_write(char *msg);
    bool BLE_checkConnection();
    int  BLE_dataAvailable();
    void BLE_changeName(char name[],bool userConncection = true);
    void BLE_Setup();
    void BLE_reset();
    void BLE_Set_Module(moduleType type);
    void sendNameInfo();
    bool ProgramENDRepotred();


  private:
  DistSensor *DistSensors[5];
  LineSensor *LineSensors[6];
  Rotor *LeftDCRotors[3];
  Rotor *RightDCRotors[3];
  LightSensor *LightSensors[4];
  bool using_BLE_Connection,connection_Break_Reported, program_End_Reported;
  moduleType BLE_MODULE_TYPE;

  #ifndef _VARIANT_BBC_MICROBIT_
  RobotLED *LEDs[5];
  Claw *Claws[2];
  Scope *Scopes[3];
  RGB_LED_Matrix *RGB_Matrix[3];
  BLEModule *BTmodule;
  #endif

  byte NDistSensors,NLEDs,NLineSensors,NScopes,NLeftDCRotors,NRightDCRotors,NClaws,NLightSensors;           //counters
  int DCSpeed = 0;
  
  #ifdef _VARIANT_BBC_MICROBIT_
  Adafruit_Microbit_Matrix ledMatrix;
  Adafruit_Microbit_BLESerial BTLESerial;
  #endif

 };

 #endif
