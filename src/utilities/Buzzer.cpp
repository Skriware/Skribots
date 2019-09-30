#include "Buzzer.h"

Buzzer::Buzzer(int pin)
  : pin(pin), volume(10), tempo(1.0)
{
  #ifdef ESP_H
    channel = SetNewPWMChannel(pin);
    ledcSetup(channel, 2000, 8);
    //ledcAttachPin(pin, channel);
  #else
    pinMode(pin, OUTPUT);
  #endif
}

void Buzzer::PlayNote(uint16_t frequency, int duration, bool blocking)
{
    #ifdef ESP_H
      ledcWrite(channel, volume);
      ledcWriteTone(channel, frequency);
    #else
      TimerFreeTone(pin, frequency, duration, volume);
    #endif

    #ifdef ESP_H
    if (blocking)
    {
      delay(duration);
        ledcWriteTone(channel, 0);
    }
    #endif
}

void Buzzer::PlayNote(uint16_t frequency)
{
  PlayNote(frequency, 0, false);
}

void Buzzer::PlayNote(const char *note)
{
  PlayNote(Buzzer::frequencyFromName(note), 0, false);
}

void Buzzer::PlayNoteAndWait(uint16_t note, int duration)
{
  PlayNote(note, duration, true);
}

void Buzzer::PlayNoteAndWait(const char *note, int duration)
{
  PlayNote(Buzzer::frequencyFromName(note), duration, true);
}

void Buzzer::StopNote(void)
{
  #ifdef ESP_H
    ledcWriteTone(channel, 0);
  #endif
}

void Buzzer::PlayMelody(const uint16_t (*melody)[2], size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    int duration = (float) melody[i][1] / tempo;
    PlayNoteAndWait(melody[i][0], duration);
  }
}

// In this case the note length is constant
void Buzzer::PlayMelody(const char **melody, size_t size)
{
  int duration = 250.0 / tempo;

  for (size_t i = 0; i < size; i++)
    PlayNoteAndWait(melody[i], duration);
}

void Buzzer::SetVolume(int volume)
{
  this->volume = volume;
}

void Buzzer::SetTempo(float tempo)
{
  this->tempo = tempo;
}

int Buzzer::frequencyFromName(const char *name)
{
  // The general formula for a note frequency n half-steps from A4=440 Hz is:
  //   f_n = f_0 * a^n
  //
  // where   f_0 = 440 Hz
  //           a = 2^(1/12) ~= 1.0594630943592953

  // Note letter/half-steps dependency:
  // A  A# B  C  C# D  D# E  F  F# G  G#
  // 0  1  2  3  4  5  6  7  8  9  10 11

  // Octave number/half-steps dependency:
  // ... A2   A3   A4   A5   A6 ...
  //    -24  -12   0    12   24

  // So we just need a note letter (with or w/out #/b) for half-step offset
  // and a number for octave offset
  // We assume that name can be 2-chars wide or 3-chars wide

  int letter_offset;
  int octave_offset;

  switch (name[0])
  {
    // C major key starts with C
    // and it's easier to calculate notes starting with it
    case 'C': letter_offset = 3; break;
    case 'D': letter_offset = 5; break;
    case 'E': letter_offset = 7; break;
    case 'F': letter_offset = 8; break;
    case 'G': letter_offset = 10; break;
    case 'A': letter_offset = 12; break;
    case 'B': letter_offset = 14; break;
  }

  char octave_number;
  // if '#' is in note name, then we increase the frequency by a half-step
  // if 'b' is in note name, --------decrease-----------------------------
  if (strlen(name) == 3)
  {
    if (name[1] == '#')
      letter_offset++;
    else if (name[1] == 'b')
      letter_offset--;
    octave_number = name[2];
  }
  else
    octave_number = name[1];

  octave_offset = 12 * (((int) octave_number - '0') - 5);

  int half_step_offset = octave_offset + letter_offset;
  int freq = A4_FREQ * pow(HALF_STEP, half_step_offset);
  return freq;
}
