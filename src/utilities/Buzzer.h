#ifndef Buzzer_H
#define Buzzer_H

// TODO:
// - volume doesn't seem to work

#include "PWM_Handler.h"
#ifndef ESP_H
  #include "./TimerFreeTone.h"
#endif

constexpr uint16_t A4_FREQ = 440;
constexpr float HALF_STEP = 1.0594630943592953;

class Buzzer
{
  public:
    Buzzer(int pin);
    void SetVolume(int volume);
    void SetTempo(float tempo);

    void PlayNote(uint16_t frequency);
    void PlayNote(const char *note);
    void PlayNoteAndWait(uint16_t note, int duration);
    void PlayNoteAndWait(const char *note, int duration);

    void PlayMelody(const uint16_t (*melody)[2], size_t size);
    void PlayMelody(const char **melody, size_t size);

    void StopNote(void);

  private:
    int pin;
    int volume;
    float tempo;
    int channel;

    void PlayNote(uint16_t frequency, int duration, bool blocking=false);
    static int frequencyFromName(const char *name);
};

#endif
