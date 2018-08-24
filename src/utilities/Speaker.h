#ifndef SPEAKER
#define SPEAKER
//#define DeBBug
#include "Arduino.h"


enum Melody {MARIO = 0,NOKIA = 1};

struct NoteToPlay{
	char note[3];
	int	duration;
};

class Speaker
{
public:
    Speaker(int _PIN,int _ID);
    int PIN;
    int ID;
    long delayTime;
    String NAME;
    NoteToPlay *note_queue[16];
    int GetID();
    void PlayMelody(Melody M,int dur = 200);
    void PlaySound(int freq, long duration,int pause_dur = 10);
    void PlaySound(int freq);
    void PlayNote(char *note, long duration,int pause_dur = 10);
    void StopSound();

};

#endif
