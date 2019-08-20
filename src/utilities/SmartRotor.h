#ifndef SMART_ROTOR_H
#define SMART_ROTOR_H

#include "PWM_Handler.h"

class SmartRotor
{
  private:
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

    // Pulses per 360 deg. turn of the robot
    int m1pulsesPerTurn;
    int m2pulsesPerTurn;

    int pulsesPerMeter;

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
    ~SmartRotor(void);

    void begin(void);

    void setSpeed(int speed);
    void setDirection(int direction);
    void setPulsesPerTurn(int pulsesPerTurn);
    void setPulsesPerMeter(int pulsesPerMeter);

    void move(void);
    // Move until a certain number of pulses is reached
    void moveByPulses(int m1pulses, int m2pulses); 
    void moveByMeters(int meters);
    void turn(bool clockwise);
    void turnByAngle(int angle);
    void stop(void);
    bool isMoving(void);
};

#endif
