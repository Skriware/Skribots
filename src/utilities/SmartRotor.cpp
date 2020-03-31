#include "SmartRotor.h"


SmartRotor *SmartRotor::sri32 = nullptr;
SmartRotor *SmartRotor::sri35 = nullptr;

SmartRotor::SmartRotor(
  uint8_t pin1,
  uint8_t pin2,
  uint8_t enc) :
    pin1(pin1),
    pin2(pin2),
    enc(enc),
    pulsesPerMeter(15050),
    pulsesPerRevolution(2500),
    pulseCount(0),
    movesToTarget(false),
    startingPulses(0),
    pulseTarget(0),
    speed(255),
    direction(1)
{
  if (enc == 32)
  {
    SmartRotor::sri32 = this;
  }
  else if (enc == 35)
  {
    SmartRotor::sri35 = this;
  }
}

SmartRotor::~SmartRotor(void)
{
  if (enc == 32)
  {
    detachInterrupt(enc);
    SmartRotor::sri32 = nullptr;
  }
  else if (enc == 35)
  {
    detachInterrupt(enc);
    SmartRotor::sri32 = nullptr;
  }
}

void SmartRotor::begin(void)
{
  pinMode(enc, INPUT);

  if (!PWM_defined(pin1))
    SetNewPWMChannel(pin1);
  if (!PWM_defined(pin2))
    SetNewPWMChannel(pin2);

  PWM_Write(pin1, 0);
  PWM_Write(pin2, 0);

  // Capture the rising edge because
  // this gives us ~25 us more for handling the interrupt
  if (enc == 32)
  {
    attachInterrupt(enc, SmartRotor::encISR32, RISING);
  }
  else if (enc == 35)
  {
    attachInterrupt(enc, SmartRotor::encISR35, RISING);
  }
}

void SmartRotor::encISR32(void)
{
  SmartRotor::sri32->pulseCount++;
}

void SmartRotor::encISR35(void)
{
  SmartRotor::sri35->pulseCount++;
}

void SmartRotor::stop(void)
{
  PWM_Write(pin1, 255);
  PWM_Write(pin2, 255);
  movesToTarget = false;
}

void SmartRotor::moveByPulses(int pulses)
{
  move();

  if (pulses > -1)
  {
    pulseTarget = pulseCount + pulses;
    movesToTarget = true;
  }
}

void SmartRotor::setDirection(int direction)
{
  this->direction = direction;
}

void SmartRotor::setSpeed(int speed)
{
  this->speed = speed;
}

void SmartRotor::move(void)
{
  if (direction == 1)
  {
    PWM_Write(pin1, speed);
    PWM_Write(pin2, 0);
  }
  else
  {
    PWM_Write(pin1, 0);
    PWM_Write(pin2, speed);
  }
}

bool SmartRotor::isMoving(void)
{
  if (movesToTarget && pulseCount >= pulseTarget)
    stop();

  return movesToTarget;
}

void SmartRotor::setPulsesPerMeter(int pulsesPerMeter)
{
  this->pulsesPerMeter = pulsesPerMeter;
}

void SmartRotor::setPulsesPerRevolution(int pulsesPerRevolution)
{
  this->pulsesPerRevolution = pulsesPerRevolution;
}

void SmartRotor::moveByMeters(float meters)
{
  moveByPulses(pulsesPerMeter * meters);
}

void SmartRotor::moveByRevolutions(float revolutions)
{
  moveByPulses(pulsesPerRevolution * revolutions);
}
