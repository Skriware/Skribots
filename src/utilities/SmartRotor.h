#ifndef SMART_ROTOR_H
#define SMART_ROTOR_H

#include "PWM_Handler.h"


/*
  This class describes a set of two rotors with encoders
*/
class SmartRotor
{
  private:
  #ifdef DEBUG_MODE
    public:
  #endif
    
    // Global SmartRotor instance for interrupts 
    static SmartRotor *_sri;

    int speed;
    int direction;

    // Driver PWM output pins
    uint8_t m1pin1;
    uint8_t m1pin2;
    uint8_t m2pin1;
    uint8_t m2pin2;

    // Encoder inputs
    uint8_t m1enc1;
    uint8_t m2enc1;
    uint8_t m1enc2;
    uint8_t m2enc2;

    // Pulses per 360 deg. turn of the whole robot
    int pulsesPerLeftTurn;
    int pulsesPerRightTurn;

    // Pulses per single rotor wheel 360 deg. turn
    int m1pulsesPerRevolution;
    int m2pulsesPerRevolution;

    int m1pulsesPerMeter;
    int m2pulsesPerMeter;

    // No. of pulses in whichever direction since the start of the program
    uint32_t m1pulseCount;
    uint32_t m2pulseCount; 

    // If set to true,
    // the flags indicate that the target is set and movement is in progress.
    bool m1movesToTarget;
    bool m2movesToTarget;

    uint32_t m1startingPulses;
    uint32_t m2startingPulses;
    uint32_t m1pulseTarget;
    uint32_t m2pulseTarget;

    void m1stop(void);
    void m2stop(void);

    static void m1encISR(void);
    static void m2encISR(void);

  public:
    enum class Which : uint8_t {
      LEFT,
      RIGHT,
      BOTH
    };

    SmartRotor(
      uint8_t m1pin1,
      uint8_t m1pin2,
      uint8_t m2pin1,
      uint8_t m2pin2,
      uint8_t m1enc1,
      uint8_t m1enc2,
      uint8_t m2enc1,
      uint8_t m2enc2
    );

    SmartRotor(
      uint8_t m1pin1,
      uint8_t m1pin2,
      uint8_t m2pin1,
      uint8_t m2pin2,
      uint8_t m1enc1,
      uint8_t m2enc1);
    
    ~SmartRotor(void);

    void begin(void);

    void setSpeed(int speed);
    void setDirection(int direction);
    void setPulsesPerTurn(int pulsesPerTurn);
    void setPulsesPerTurn(int pulsesPerLeftTurn, int pulsesPerRightTurn);
    void setPulsesPerMeter(int pulsesPerMeter);
    void setPulsesPerMeter(int m1pulsesPerMeter, int m2pulsesPerMeter);
    void setPulsesPerRevolution(int pulsesPerRevolution);
    void setPulsesPerRevolution(
      int m1pulsesPerRevolution, int m2pulsesPerRevolution);

    void move(void);
    // Move until a certain number of pulses is reached
    void moveByPulses(int m1pulses, int m2pulses); 
    void moveByMeters(float meters, Which rotor=Which::BOTH);
    void moveByRevolutions(float revolutions, Which rotor=Which::BOTH);
    void turn(bool clockwise);
    void turnByAngle(int angle);
    void turnByRevolutions(float revolutions);
    void stop(void);
    bool isMoving(void);
};

#endif
