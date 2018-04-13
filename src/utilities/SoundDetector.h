#ifndef SoundDet_H
#define SoundDet_H
#include "Arduino.h"
  class SoundDetector
 {
  public:
    SoundDetector(int OutputPin ,String name);
    int CountSound(int seconds);
    static void SoundDetected();
    String name();
    static long times[5];
    static int Nsignal;
  private:
  int _out_pin;
  String _name;
 };

 #endif