#ifndef BUTTONS_H
#define BUTTONS_H

#include "Arduino.h"

#define BUTTONS_BTN_DECL(p_) extern bool button ## p_ ## Available; \
extern volatile uint32_t button ## p_ ## LastTimeUp; \
extern volatile uint32_t button ## p_ ## LastTimeDown; \
extern volatile bool button ## p_ ## EventPending; \
void button ## p_ ## Handler(void);

#define BUTTONS_BTN_DEF(p_) bool button ## p_ ## Available = false; \
volatile uint32_t button ## p_ ## LastTimeUp = 0; \
volatile uint32_t button ## p_ ## LastTimeDown = 0; \
volatile bool button ## p_ ## EventPending = false; \
void button ## p_ ## Handler(void) \
{ \
  if (digitalRead(p_)) \
  { \
    button ## p_ ## LastTimeUp = millis(); \
    if (button ## p_ ## LastTimeUp - button ## p_ ## LastTimeDown > 0) \
      button ## p_ ## EventPending = true; \
  } \
  else if (millis() - button ## p_ ## LastTimeUp > buttonEventInterval) \
    button ## p_ ## LastTimeDown = millis(); \
}

#define BUTTONS_BTN_ENABLE_CASE(p_) case p_: \
  pinMode(p_, INPUT_PULLUP); \
  button ## p_ ## Available = true; \
  attachInterrupt(p_, button ## p_ ## Handler, CHANGE); \
  break;

#define BUTTONS_BTN_DISABLE_CASE(p_) case p_: \
  detachInterrupt(p_); \
  break;

#define BUTTONS_BTN_EVENT_CASE(p_) case p_: \
  return button ## p_ ## EventPending; \
  break;

#define BUTTONS_BTN_CLEAR_EVENT_CASE(p_) case p_: \
  button ## p_ ## EventPending = false; \
  break;

#define BUTTONS_BTN_PRESSED_CASE(p_) case p_: \
  if (millis() - button ## p_ ## LastTimeUp < buttonPressInterval) \
    return true; \
  break;

#define BUTTONS_BTN_HELD_CASE(p_) case p_: \
  if (!digitalRead(p_) && ((button ## p_ ## LastTimeUp < button ## p_ ## LastTimeDown \
      && millis() - button ## p_ ## LastTimeDown >= heldFor) \
    || (button ## p_ ## LastTimeUp >= button ## p_ ## LastTimeDown \
      && button ## p_ ## LastTimeUp - button ## p_ ## LastTimeDown >= heldFor))) \
    return true; \
  break;


static const uint32_t buttonPressInterval = 75;
static const uint32_t buttonEventInterval = 50;

BUTTONS_BTN_DECL(12);
BUTTONS_BTN_DECL(13);
BUTTONS_BTN_DECL(14);
BUTTONS_BTN_DECL(15);
BUTTONS_BTN_DECL(25);
BUTTONS_BTN_DECL(26);
BUTTONS_BTN_DECL(27);

BUTTONS_BTN_DECL(34);
BUTTONS_BTN_DECL(36);
BUTTONS_BTN_DECL(39);

void buttonEnable(int pin);
void buttonDisable(int pin);
bool buttonReadRaw(int pin);
bool buttonRead(int pin);
bool buttonEventPending(int pin);
void buttonClearEvent(int pin);
bool buttonPressed(int pin);
bool buttonHeld(int pin, uint32_t heldFor);

#endif
