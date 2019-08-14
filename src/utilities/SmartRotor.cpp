#include "SmartRotor.h"

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
    m1pulsesPerTurn(6500),
    m2pulsesPerTurn(6500),
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
  pinMode(m1enc1, INPUT);
  pinMode(m1enc2, INPUT);
  pinMode(m2enc1, INPUT);
  pinMode(m2enc2, INPUT);

  SetNewPWMChannel(m1pin1);
  SetNewPWMChannel(m1pin2);
  SetNewPWMChannel(m2pin1);
  SetNewPWMChannel(m2pin2);

  PWM_Write(m1pin1, 0);
  PWM_Write(m1pin2, 0);
  PWM_Write(m2pin1, 0);
  PWM_Write(m2pin2, 0);
}

// enc2 param is now unused
// but may later be useful for detecting CW/CCW rotation
void SmartRotor::pulseISR(uint8_t enc1, uint8_t enc2, uint32_t *pulseCounter)
{
  if (digitalRead(enc1))
    *pulseCounter++;
}

void SmartRotor::m1pulseISR(void)
{
  if (digitalRead(m1enc1))
    m1pulseCount++;

  if (m1movesToTarget && m1pulseCount >= m1pulseTarget)
    m1stop();
}

void SmartRotor::m2pulseISR(void)
{
  if (digitalRead(m2enc1))
    m2pulseCount++;

  if (m2movesToTarget && m2pulseCount >= m2pulseTarget)
    m2stop();
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
  int a = angle;
  if (angle < 0)
  {
    cw = false;
    a = -a;
  }
    
  m1pulseTarget = m1pulseCount + (int) (m1pulsesPerTurn * ((double)a/360.0));
  m2pulseTarget = m2pulseCount + (int) (m2pulsesPerTurn * ((double)a/360.0));
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

void SmartRotor::setPulsesPerTurn(int pulsesPerTurn)
{
  this->m1pulsesPerTurn = pulsesPerTurn;
  this->m2pulsesPerTurn = pulsesPerTurn;
}