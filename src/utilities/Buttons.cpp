#include "Buttons.h"

BUTTONS_BTN_DEF(12);
BUTTONS_BTN_DEF(13);
BUTTONS_BTN_DEF(14);
BUTTONS_BTN_DEF(15);
BUTTONS_BTN_DEF(25);
BUTTONS_BTN_DEF(26);
BUTTONS_BTN_DEF(27);

void buttonEnable(int pin)
{
  switch (pin)
  {
    BUTTONS_BTN_ENABLE_CASE(12);
    BUTTONS_BTN_ENABLE_CASE(13);
    BUTTONS_BTN_ENABLE_CASE(14);
    BUTTONS_BTN_ENABLE_CASE(15);
    BUTTONS_BTN_ENABLE_CASE(25);
    BUTTONS_BTN_ENABLE_CASE(26);
    BUTTONS_BTN_ENABLE_CASE(27);
  }
}

void buttonDisable(int pin)
{
  switch (pin)
  {
    BUTTONS_BTN_DISABLE_CASE(12);
    BUTTONS_BTN_DISABLE_CASE(13);
    BUTTONS_BTN_DISABLE_CASE(14);
    BUTTONS_BTN_DISABLE_CASE(15);
    BUTTONS_BTN_DISABLE_CASE(25);
    BUTTONS_BTN_DISABLE_CASE(26);
    BUTTONS_BTN_DISABLE_CASE(27);
  }
}

bool buttonReadRaw(int pin)
{
  return digitalRead(pin);
}

bool buttonRead(int pin)
{
  return !digitalRead(pin);
}

bool buttonEventPending(int pin)
{
  switch (pin)
  {
    BUTTONS_BTN_EVENT_CASE(12);
    BUTTONS_BTN_EVENT_CASE(13);
    BUTTONS_BTN_EVENT_CASE(14);
    BUTTONS_BTN_EVENT_CASE(15);
    BUTTONS_BTN_EVENT_CASE(25);
    BUTTONS_BTN_EVENT_CASE(26);
    BUTTONS_BTN_EVENT_CASE(27);
  }
}

bool buttonPressed(int pin)
{
  switch (pin)
  {
    BUTTONS_BTN_PRESSED_CASE(12);
    BUTTONS_BTN_PRESSED_CASE(13);
    BUTTONS_BTN_PRESSED_CASE(14);
    BUTTONS_BTN_PRESSED_CASE(15);
    BUTTONS_BTN_PRESSED_CASE(25);
    BUTTONS_BTN_PRESSED_CASE(26);
    BUTTONS_BTN_PRESSED_CASE(27);
  }
  
  return false;
}

bool buttonHeld(int pin, uint32_t heldFor)
{
  switch (pin)
  {
    BUTTONS_BTN_HELD_CASE(12);
    BUTTONS_BTN_HELD_CASE(13);
    BUTTONS_BTN_HELD_CASE(14);
    BUTTONS_BTN_HELD_CASE(15);
    BUTTONS_BTN_HELD_CASE(25);
    BUTTONS_BTN_HELD_CASE(26);
    BUTTONS_BTN_HELD_CASE(27);
  }

  return false;
}

void buttonClearEvent(int pin)
{
  switch (pin)
  {
    BUTTONS_BTN_CLEAR_EVENT_CASE(12);
    BUTTONS_BTN_CLEAR_EVENT_CASE(13);
    BUTTONS_BTN_CLEAR_EVENT_CASE(14);
    BUTTONS_BTN_CLEAR_EVENT_CASE(15);
    BUTTONS_BTN_CLEAR_EVENT_CASE(25);
    BUTTONS_BTN_CLEAR_EVENT_CASE(26);
    BUTTONS_BTN_CLEAR_EVENT_CASE(27);
  }
}
