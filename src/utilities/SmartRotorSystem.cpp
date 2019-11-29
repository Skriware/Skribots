#include "SmartRotorSystem.h"


SmartRotorSystem::SmartRotorSystem(void)
{
}

SmartRotorSystem::SmartRotorSystem(SmartRotor *left, SmartRotor *right)
{
  this->left = left;
  this->right = right;
}

SmartRotorSystem::SmartRotorSystem(
  uint8_t leftPin1, uint8_t leftPin2, uint8_t leftEnc,
  uint8_t rightPin1, uint8_t rightPin2, uint8_t rightEnc
)
{
  left = new SmartRotor(leftPin1, leftPin2, leftEnc);
  right = new SmartRotor(rightPin1, rightPin2, rightEnc);
}

SmartRotorSystem::~SmartRotorSystem(void)
{
  delete left;
  delete right;
}

void SmartRotorSystem::setTurnDirections(bool cw)
{
  if (cw)
  {
    left->setDirection(1);
    right->setDirection(0);
  }
  else
  {
    left->setDirection(0);
    right->setDirection(1);
  }
}

void SmartRotorSystem::setNormalDirections(void)
{
  if (direction == 1)
  {
    left->setDirection(1);
    right->setDirection(1);
  }
  else
  {
    left->setDirection(0);
    right->setDirection(0);
  }
}

void SmartRotorSystem::begin(bool recursive)
{
  setPulsesPerTurn(9000);
  setDirection(1);
  setSpeed(255);

  if (recursive)
  {
    left->begin();
    right->begin();
  }
}

void SmartRotorSystem::setSpeed(int speed)
{
  left->setSpeed(speed);
  right->setSpeed(speed);
}

void SmartRotorSystem::setDirection(int direction)
{
  this->direction = direction;
}

void SmartRotorSystem::setPulsesPerTurn(int pulsesPerLeftTurn, int pulsesPerRightTurn)
{
  this->pulsesPerLeftTurn = pulsesPerLeftTurn;
  this->pulsesPerRightTurn = pulsesPerRightTurn;
}

void SmartRotorSystem::setPulsesPerTurn(int pulsesPerTurn)
{
  setPulsesPerTurn(pulsesPerTurn, pulsesPerTurn);
}

void SmartRotorSystem::setPulsesPerMeter(int leftPulsesPerMeter, int rightPulsesPerMeter)
{
  left->pulsesPerMeter = leftPulsesPerMeter;
  right->pulsesPerMeter = rightPulsesPerMeter;
}

void SmartRotorSystem::setPulsesPerMeter(int pulsesPerMeter)
{
  setPulsesPerMeter(pulsesPerMeter, pulsesPerMeter);
}

void SmartRotorSystem::setPulsesPerRevolution(int leftPulsesPerRevolution, int rightPulsesPerRevolution)
{
  left->pulsesPerRevolution = leftPulsesPerRevolution;
  right->pulsesPerRevolution = rightPulsesPerRevolution;
}

void SmartRotorSystem::setPulsesPerRevolution(int pulsesPerRevolution)
{
  setPulsesPerRevolution(pulsesPerRevolution, pulsesPerRevolution);
}

void SmartRotorSystem::move(void)
{
  if (direction == 1)
  {
    left->setDirection(1);
    right->setDirection(1);
  }
  else
  {
    left->setDirection(0);
    right->setDirection(0);
  }

  left->move();
  right->move();
}

void SmartRotorSystem::moveByPulses(int leftPulses, int rightPulses)
{
  setNormalDirections();
  left->moveByPulses(leftPulses);
  right->moveByPulses(rightPulses);
}

void SmartRotorSystem::moveByMeters(float meters, SmartRotorSystem::Which rotor)
{
  setNormalDirections();
  switch (rotor)
  {
    case Which::LEFT:
      left->moveByMeters(meters);
      break;
    case Which::RIGHT:
      right->moveByMeters(meters);
      break;
    case Which::BOTH:
      left->moveByMeters(meters);
      right->moveByMeters(meters);
      break;
  }
}

void SmartRotorSystem::moveByRevolutions(
  float revolutions, SmartRotorSystem::Which rotor)
{
  setNormalDirections();
  switch (rotor)
  {
    case Which::LEFT:
      left->moveByRevolutions(revolutions);
      break;
    case Which::RIGHT:
      right->moveByRevolutions(revolutions);
      break;
    case Which::BOTH:
      left->moveByRevolutions(revolutions);
      right->moveByRevolutions(revolutions);
      break;
  }
}

void SmartRotorSystem::turn(bool clockwise)
{
  setTurnDirections(clockwise);

  left->move();
  right->move();
}

void SmartRotorSystem::turnByAngle(int angle)
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

  setTurnDirections(cw);

  left->moveByPulses((int) (ppt * ((float) a/360.0)));
  right->moveByPulses((int) (ppt * ((float) a/360.0)));
}

void SmartRotorSystem::turnByRevolutions(float revolutions)
{
  bool cw = true;

  int revs = revolutions;

  if (revolutions < 0)
  {
    cw = false;
    revs = -revs;
  }

  setTurnDirections(cw);

  left->moveByPulses((int) (left->pulsesPerRevolution * revs));
  right->moveByPulses((int) (right->pulsesPerRevolution * revs));
}

void SmartRotorSystem::stop()
{
  left->stop();
  right->stop();
}

bool SmartRotorSystem::isMoving()
{
  return left->isMoving() || right->isMoving();
}
