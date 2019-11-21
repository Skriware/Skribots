#ifndef SMART_ROTOR_H
#define SMART_ROTOR_H

#include "PWM_Handler.h"


/*
  This class describes a single rotor with encoders
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
    uint8_t pin1;
    uint8_t pin2;

    // Encoder inputs
    uint8_t enc;

    int pulsesPerRevolution;
    int pulsesPerMeter;

    // No. of pulses in whichever direction since the start of the program
    uint32_t pulseCount;

    // If set to true,
    // this flag indicates that the target is set and movement is in progress.
    bool movesToTarget;

    uint32_t startingPulses;
    uint32_t pulseTarget;

    void stop(void);

    static void encISR(void);

  public:
    SmartRotor(
      uint8_t pin1,
      uint8_t pin2,
      uint8_t enc1,
    );
    
    ~SmartRotor(void);

    void begin(void);

    void setSpeed(int speed);
    void setDirection(int direction);
    void setPulsesPerTurn(int pulsesPerTurn);
    void setPulsesPerMeter(int pulsesPerMeter);
    void setPulsesPerRevolution(int pulsesPerRevolution);

    void move(void);
    // Move until a certain number of pulses is reached
    void moveByPulses(int pulses);
    void moveByMeters(float meters);
    void moveByRevolutions(float revolutions);
    void stop(void);
    bool isMoving(void);
};

#endif
