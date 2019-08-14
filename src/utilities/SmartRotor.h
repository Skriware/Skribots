#ifndef SMART_ROTOR_H
#define SMART_ROTOR_H

#include "PWM_Handler.h"

class SmartRotor
{
  private:
    int speed;
    int direction;

    // Driver PWM output pins
    uint8_t m1pin1;
    uint8_t m1pin2;
    uint8_t m2pin1;
    uint8_t m2pin2;

    // Encoder inputs
    uint8_t m1enc2;
    uint8_t m2enc2;

    // Pulses per 360 deg. turn of the robot
    int m1pulsesPerTurn;
    int m2pulsesPerTurn;

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

    // Move until a certain number of pulses is reached
    void moveByPulses(int m1pulses, int m2pulses); 

    void m1stop(void);
    void m2stop(void);

    // generic encoder interrupt handler
    void pulseISR(uint8_t enc1, uint8_t enc2, uint32_t *pulseCounter);

  public:
    // Encoder input pins
    // These are public because they are used for triggering the interrupts
    uint8_t m1enc1;
    uint8_t m2enc1;

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

    void setSpeed(int speed);
    void setDirection(int direction);
    void setPulsesPerTurn(int pulsesPerTurn);

    void move(void);
    void turn(bool clockwise);
    void turnByAngle(int angle);
    void stop(void);

    // These two ISRs should be used in the following manner:
    // 
    // void m1encoderISR(void)
    // {
    //    smartmotor->m1pulseISR();
    // }
    // ...
    // attachInterrupt(smartmotor->m1enc1, m1encoderISR, CHANGE);
    void m1pulseISR(void);
    void m2pulseISR(void);
};

#endif