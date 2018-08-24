#include "LightSensor.h"

LightSensor::LightSensor(int _PIN,int _ID){
    PIN = _PIN;
    ID = _ID;
    CalibrateLight();
}

int LightSensor::ReadRaw(){
    return(analogRead(PIN));   
}

void LightSensor::CalibrateLight(){
    int Reads[100]; 
    for (int i=0; i < 100; i++){
        Reads[i] = ReadRaw();
        delay(30);
    }

#ifdef DEBUG_MODE
    Serial.print("Calibrating Light Sensor ");
    Serial.print(ID);
    Serial.println(":");
    for(int i = 0; i < 100; i++)
    {
        Serial.print(Reads[i]);
        Serial.print(" ");
        if(i%10 == 0 )Serial.println();
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
    
    avrage = Reads_new[39];
    threshold = 50+(Reads[79]-Reads[0]);

    #ifdef DEBUG_MODE
    Serial.print("Avrage:");
    Serial.println(avrage);
    Serial.print("Threshold:");
    Serial.println(threshold);
    #endif

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