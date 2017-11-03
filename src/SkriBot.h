#ifndef SkriBot_H
#define SkriBot_H
#include "Arduino.h"
#include <utilities/ServoRotor.h>
#include <utilities/DistSensor.h>
#include <utilities/RobotLED.h>
#include <utilities/LineSensor.h>
#include <utilities/Scope.h>
#include <StandardCplusplus.h>
#include <utilities/BlueDentist.h>
#include <utilities/Rotor.h>
#include <utilities/SoundDetector.h>
#include <vector>

  class SkriBot
 {
  public:
  	SkriBot();
  	void AddRotor(int Pin,String Side, int neutral = 1520); 
  	void AddDistSensor(int EchoPin,int TrigPin,String Name);
    void AddDistSensor(int EchoPin,int TrigPin,int id);
    void AddLED(int Pin,String name);
    void AddLineSensor(int Pin, String Name); 
    void AddLineSensor(int Pin, int id);
    void AddScope(int EchoPin,int Trigg,int ServoPin,String Name);
    void AddDCRotor(int SpeedPin,int DirectionPin, String side);
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

    void TurnOnLED(String name);
    void TurnOffLED(String name);                                 // LED functions

    int ReadLineSensor(String name);
    int ReadLineSensor(int id);
                                                                 // line sensor readout
    void SetScopeAngle(String id, int deg);  
    int  GetScopeDistance(String id);                               //Scope functions
  private:
  std::vector<ServoRotor> LeftRotors;
  std::vector<ServoRotor> RightRotors;
  std::vector<DistSensor> DistSensors;
  std::vector<RobotLED> LEDs;
  std::vector<LineSensor> LineSensors;
  std::vector<Scope> Scopes;
  std::vector<Rotor> LeftDCRotors;
  std::vector<Rotor> RightDCRotors;
  int DCSpeed = 0;
 };

 #endif
