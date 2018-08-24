#ifndef LIGHTSENSOR
#define LIGHTSENSOR
//#define DEBUG_MODE
#include "Arduino.h"

class LightSensor 
{
public:
    LightSensor(int _PIN,int _ID);
    int PIN;
    int ID;
    int avrage;
    int threshold;
    String NAME;
    int ReadRaw();
    void CalibrateLight();
    bool isDark();
    bool isBright();
    int GetID();
};

#endif

