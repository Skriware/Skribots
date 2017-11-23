#ifndef SkriBot_H
#define SkriBot_H
#include "Arduino.h"
#include <utilities/ServoRotor.h>
#include <utilities/DistSensor.h>
#include <utilities/RobotLED.h>
#include <utilities/LineSensor.h>
#include <utilities/Scope.h>
#include <StandardCplusplus.h>
#include <utilities/Rotor.h>
#include <utilities/SoundDetector.h>
#include <utilities/Claw.h>
#include <Adafruit_NeoPixel.h>

  class SkriBot
 {
  public:
  	SkriBot();
  	void AddDistSensor(int EchoPin,int TrigPin,String Name);
    void AddDistSensor(int EchoPin,int TrigPin,int id);
    void AddLED(int Pin,String name);
    void AddLineSensor(int Pin, String Name); 
    void AddLineSensor(int Pin, int id);
    void AddScope(int EchoPin,int Trigg,int ServoPin,String Name);
    void AddDCRotor(int SpeedPin,int DirectionPin, String side);
    void AddClaw(int ClawPin,int Arm_Pin, byte id = 0);
                                                                  //functions for element adding

    void Move(char Direction,int ms);
    void FaceLeft(int ms = 200);
    void FaceRight(int ms = 200);
    void TurnLeft(int ms = 200);
    void TurnRight(int ms = 200);
    void MoveForward(int ms = -1);
    void MoveBack(int ms = -1);
    void RawRotorMove(int left,int right);
    void Stop();   

    void SetSpeed(int speed);                                               //functions for movements

    int ReadDistSensor(String id, int max = 100);
    int ReadDistSensor(int id, int max = 100);
                                                                  //distance sensor readout

    void TurnLEDOn(int R,int G, int B,String name);
    void TurnLEDOff(String name); 
    void TurnLEDOn(int R,int G, int B,int _id = -69);
    void TurnLEDOff(int _id = -69);                                // LED functions

    void CloseClaw(byte id = 0);
    void OpenClaw(byte id  = 0);
    void Pick_Up(byte id = 0);
    void Put_Down(byte id = 0);                                              //Claw functins

    int ReadLineSensor(String name);
    int ReadLineSensor(int id);
                                                                 // line sensor readout
    void SetScopeAngle(String id, int deg);  
    int  GetScopeDistance(String id);                               //Scope functions
  private:
 
  DistSensor *DistSensors[5];
  RobotLED *LEDs[5];
  LineSensor *LineSensors[6];
  Scope *Scopes[3];
  Rotor *LeftDCRotors[3];
  Rotor *RightDCRotors[3];
  Claw *Claws[2];
  byte NDistSensors,NLEDs,NLineSensors,NScopes,NLeftDCRotors,NRightDCRotors,NClaws;           //counters
  int DCSpeed = 0;

 };

 #endif
