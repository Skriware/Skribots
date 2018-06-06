#include "LightSensor.h"

LightSensor::LightSensor(int _PIN,int _ID){
    PIN = _PIN;
    ID = _ID;
    TestLight();
}

int LightSensor::ReadRaw(){
    return(analogRead(PIN));   
}

void LightSensor::TestLight(){
    int Reads[100]; 
    for (int i=0; i < 100; i++){
        Reads[i] = ReadRaw();
        delay(30);
    }

#ifdef Debug
    for(int i = 0; i < 100; i++)
    {
        Serial.println(Reads[i]);
    }
#endif

    for (int i=0; i < 100; i++){
        if (i==49 && Reads[i-1]>Reads[i]){
            int t= Reads[i];
            Reads [i] = Reads [i-1];
            Reads [i-1] = t;
            t=0;
        }
        else if (Reads[i] > Reads[i+1]){
            int t= Reads[i];
            Reads [i] = Reads [i+1];
            Reads [i+1] = t;
            t=0;
        }
    }
    int Reads_new[80];
    for(int i = 0; i < 80; i++)
    {
        Reads_new[i] = Reads[9+i];
    }


#ifdef Debug
    Serial.println("UPORZADKOWANA");
    for(int i = 0; i < 80; i++)
    {
        Serial.println(Reads_new[i]);
    }
#endif
    
    avrage = Reads_new[39];
    threshold = avrage*0.1+(Reads[79]-Reads[0]);

}

bool LightSensor::isDark(){
    if ((avrage+threshold) > ReadRaw())
        return false;
    else
        return true;

}

bool LightSensor::isBright(){
      if ((avrage-threshold) < ReadRaw())
        return false;
    else
        return true;

}

int LightSensor::GetID(){
    return(ID);
}