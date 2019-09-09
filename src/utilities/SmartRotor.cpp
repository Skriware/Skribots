#include "SmartRotor.h"

SmartRotor *SmartRotor::_sri = nullptr;

SmartRotor::SmartRotor(
  uint8_t m1pin1,
  uint8_t m1pin2,
  uint8_t m2pin1,
  uint8_t m2pin2,
  uint8_t m1enc1,
  uint8_t m1enc2,
  uint8_t m2enc1,
  uint8_t m2enc2) :
    m1pin1(m1pin1),
    m1pin2(m1pin2),
    m2pin1(m2pin1),
    m2pin2(m2pin2),
    m1enc1(m1enc1),
    m1enc2(m1enc2),
    m2enc1(m2enc1),
    m2enc2(m2enc2),
    pulsesPerLeftTurn(9000),
    pulsesPerRightTurn(9000),
    m1pulsesPerMeter(15050),
    m2pulsesPerMeter(15050),
    m1pulseCount(0),
    m2pulseCount(0),
    m1movesToTarget(false),
    m2movesToTarget(false),
    m1startingPulses(0),
    m2startingPulses(0),
    m1pulseTarget(0),
    m2pulseTarget(0),
    speed(255),
    direction(1)
{
  SmartRotor::_sri = this;
}

SmartRotor::SmartRotor(
  uint8_t m1pin1,
  uint8_t m1pin2,
  uint8_t m2pin1,
  uint8_t m2pin2,
  uint8_t m1enc1,
  uint8_t m2enc1) : SmartRotor::SmartRotor(
    m1pin1, m1pin2, m2pin1, m2pin2, m1enc1, -1, m2enc1, -1)
{
}

SmartRotor::~SmartRotor(void)
{
  SmartRotor::_sri = nullptr;
}

void SmartRotor::m1encISR(void)
{
  if (SmartRotor::_sri != nullptr)
  {
    if (digitalRead(SmartRotor::_sri->m1enc1))
      SmartRotor::_sri->m1pulseCount++;

    if (SmartRotor::_sri->m1movesToTarget &&
      SmartRotor::_sri->m1pulseCount >= SmartRotor::_sri->m1pulseTarget)
    {
      SmartRotor::_sri->m1stop();
    }
  }
}

void SmartRotor::m2encISR(void)
{
  if (SmartRotor::_sri != nullptr)
  {
    if (digitalRead(SmartRotor::_sri->m2enc1))
      SmartRotor::_sri->m2pulseCount++;

    if (SmartRotor::_sri->m2movesToTarget &&
      SmartRotor::_sri->m2pulseCount >= SmartRotor::_sri->m2pulseTarget)
    {
      SmartRotor::_sri->m2stop();
    }
  }
}

void SmartRotor::m1stop(void)
{
  PWM_Write(m1pin1, 255);
  PWM_Write(m1pin2, 255);
  m1movesToTarget = false;
}

void SmartRotor::m2stop(void)
{
  PWM_Write(m2pin1, 255);
  PWM_Write(m2pin2, 255);
  m2movesToTarget = false;
}

void SmartRotor::stop(void)
{
  m1stop();
  m2stop();
}

void SmartRotor::turnByAngle(int angle)
{
  bool cw = true;
  int ppt = pulsesPerRightTurn;
  int a = angle;
  if (angle < 0)
  {
    cw = false;
    ppt = pulsesPerLeftTurn;
    a = -a;
  }

  m1pulseTarget = m1pulseCount + (int) (ppt * ((double)a/360.0));
  m2pulseTarget = m2pulseCount + (int) (ppt * ((double)a/360.0));
  m1movesToTarget = true;
  m2movesToTarget = true;

  turn(cw);
}

void SmartRotor::moveByPulses(int m1pulses, int m2pulses)
{
  m1pulseTarget = m1pulseCount + m1pulses;
  m2pulseTarget = m2pulseCount + m2pulses;

  m1movesToTarget = true;
  m2movesToTarget = true;

  move();
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
    PWM_Write(m1pin1, speed);
    PWM_Write(m1pin2, 0);
    PWM_Write(m2pin1, 0);
    PWM_Write(m2pin2, speed);
  }
  else
  {
    PWM_Write(m1pin1, 0);
    PWM_Write(m1pin2, speed);
    PWM_Write(m2pin1, speed);
    PWM_Write(m2pin2, 0);
  }
}

void SmartRotor::turn(bool clockwise)
{
  if (clockwise)
  {
    PWM_Write(m1pin1, speed);
    PWM_Write(m1pin2, 0);
    PWM_Write(m2pin1, speed);
    PWM_Write(m2pin2, 0);
  }
  else
  {
    PWM_Write(m1pin1, 0);
    PWM_Write(m1pin2, speed);
    PWM_Write(m2pin1, 0);
    PWM_Write(m2pin2, speed);
  }
}

void SmartRotor::begin(void)
{
  pinMode(m1enc1, INPUT);
  pinMode(m2enc1, INPUT);

  if (m1enc2 > 0)
    pinMode(m1enc2, INPUT);
  
  if (m2enc2 > 0)
    pinMode(m2enc2, INPUT);

  SetNewPWMChannel(m1pin1);
  SetNewPWMChannel(m1pin2);
  SetNewPWMChannel(m2pin1);
  SetNewPWMChannel(m2pin2);

  PWM_Write(m1pin1, 0);
  PWM_Write(m1pin2, 0);
  PWM_Write(m2pin1, 0);
  PWM_Write(m2pin2, 0);

  attachInterrupt(m1enc1, &SmartRotor::m1encISR, CHANGE);
  attachInterrupt(m2enc1, &SmartRotor::m2encISR, CHANGE);
}

bool SmartRotor::isMoving(void)
{
  return m1movesToTarget || m2movesToTarget;
}

void SmartRotor::setPulsesPerMeter(int pulsesPerMeter)
{
  m1pulsesPerMeter = pulsesPerMeter;
  m2pulsesPerMeter = pulsesPerMeter;
}

// Set pulses per 1 meter for both motors
// if value for a motor is < 0, the value remains unchanged
void SmartRotor::setPulsesPerMeter(int m1pulsesPerMeter, int m2pulsesPerMeter)
{
  if (m1pulsesPerMeter >= 0)
    this->m1pulsesPerMeter = m1pulsesPerMeter;

  if (m2pulsesPerMeter >= 0)
    this->m2pulsesPerMeter = m2pulsesPerMeter;
}

void SmartRotor::setPulsesPerTurn(int pulsesPerTurn)
{
  pulsesPerLeftTurn = pulsesPerTurn;
  pulsesPerRightTurn = pulsesPerTurn;
}
 
// If value for a direction is < 0, the value remains unchanged
void SmartRotor::setPulsesPerTurn(int pulsesPerLeftTurn, int pulsesPerRightTurn)
{
  if (pulsesPerLeftTurn >= 0)
    this->pulsesPerLeftTurn = pulsesPerLeftTurn;
  
  if (pulsesPerRightTurn >= 0)
    this->pulsesPerRightTurn = pulsesPerRightTurn;
}

void SmartRotor::moveByMeters(float meters)
{
  moveByPulses(m1pulsesPerMeter * meters, m2pulsesPerMeter * meters);
}
