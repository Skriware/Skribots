#ifndef SMART_ROTOR_SYSTEM_H
#define SMART_ROTOR_SYSTEM_H

#include "SmartRotor.h"

class SmartRotorSystem
{
  SmartRotor *left;
  SmartRotor *right;

  int pulsesPerLeftTurn;
  int pulsesPerRightTurn;
  int direction;

  void setTurnDirections(bool cw);
  void setNormalDirections(void);

  public:
    enum class Which : uint8_t
    {
      LEFT,
      RIGHT,
      BOTH
    };

    SmartRotorSystem(void);
    SmartRotorSystem(SmartRotor *left, SmartRotor *right);
    SmartRotorSystem(
      uint8_t leftPin1, uint8_t leftPin2, uint8_t leftEnc,
      uint8_t rightPin1, uint8_t rightPin2, uint8_t rightEnc
    );
    ~SmartRotorSystem(void);

    void begin(bool recursive=false);

    void setSpeed(int speed);
    void setDirection(int direction);

    void setPulsesPerTurn(int pulsesPerLeftTurn, int pulsesPerRightTurn);
    void setPulsesPerTurn(int pulsesPerTurn);
    void setPulsesPerMeter(int leftPulsesPerMeter, int rightPulsesPerMeter);
    void setPulsesPerMeter(int pulsesPerMeter);
    void setPulsesPerRevolution(
      int leftPulsesPerRevolution, int rightPulsesPerRevolution);
    void setPulsesPerRevolution(int pulsesPerRevolution);

    void move(void);
    void moveByPulses(int leftPulses, int rightPulses);
    void moveByMeters(float meters, Which rotor=Which::BOTH);
    void moveByRevolutions(float revolutions, Which rotor=Which::BOTH);

    void turn(bool clockwise);
    void turnByAngle(int angle);
    void turnByRevolutions(float revolutions);
    void stop(void);
    bool isMoving(void);
};

#endif
