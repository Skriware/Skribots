#include "SmartRotor.h"

// A hash map of instances of SmartRotor
std::unordered_map<uint8_t, SmartRotor *> SmartRotor::_sri = {};

// A hash map of possible ISRs for encoder pins
std::unordered_map<uint8_t, void (*)()> SmartRotor::_sri_isr = {
  {32, SmartRotor::encISR<32>},
  {35, SmartRotor::encISR<35>},
};

bool SmartRotor::isRegisteredInstance(uint8_t enc_)
{
  return SmartRotor::_sri.find(enc_) != SmartRotor::_sri.end();
}

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
  if (SmartRotor::isRegisteredInstance(enc))
    delete SmartRotor::_sri[enc];

  SmartRotor::_sri[enc] = this;
}

SmartRotor::~SmartRotor(void)
{
  if (SmartRotor::isRegisteredInstance(enc))
    SmartRotor::_sri.erase(enc);
}

template <uint8_t enc_>
void SmartRotor::encISR(void)
{
  if (SmartRotor::isRegisteredInstance(enc_))
  {
    if (digitalRead(SmartRotor::_sri[enc_]->enc))
      SmartRotor::_sri[enc_]->pulseCount++;

    if (SmartRotor::_sri[enc_]->movesToTarget &&
      SmartRotor::_sri[enc_]->pulseCount >= SmartRotor::_sri[enc_]->pulseTarget)
    {
      SmartRotor::_sri[enc_]->stop();
    }
  }
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
  else
  {
    movesToTarget = false;
    stop();
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

void SmartRotor::begin(void)
{
  pinMode(enc, INPUT);

  SetNewPWMChannel(pin1);
  SetNewPWMChannel(pin2);

  PWM_Write(pin1, 0);
  PWM_Write(pin2, 0);

  attachInterrupt(enc, SmartRotor::_sri_isr[enc], CHANGE);
}

bool SmartRotor::isMoving(void)
{
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
