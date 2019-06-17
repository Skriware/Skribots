#include "Speaker.h"


Speaker::Speaker(int _PIN,int _ID){
    PIN = _PIN;
    ID = _ID;
    delayTime = 0;
    pinMode(PIN, OUTPUT);
    
}

void Speaker::PlaySound(int freq_Hz, long duration_ms, int pause_dur){
     PlaySound(freq_Hz);
     long Ntimes = duration_ms*1000/delayTime/2;
     for(long yy = 0; yy < Ntimes; yy++){
        digitalWrite(PIN,HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(PIN,LOW);
        delayMicroseconds(delayTime);
     }
     delay(pause_dur);
}

void Speaker::PlaySound(int freq_Hz){
    delayTime = 500000/freq_Hz; //0.5 of the tone cycel 
}

void Speaker::StopSound(){
      
}

void Speaker::PlayMelody(Melody M,int duration){

    int dur = duration;
    switch(M){
        case MARIO:
 this->PlayNote("E4",dur);
 this->PlayNote("E4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("E4",dur);

 this->PlayNote("O",dur);
 this->PlayNote("C4",dur);
 this->PlayNote("E4",dur);
 this->PlayNote("O",dur);

 this->PlayNote("G4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);

 this->PlayNote("G3",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);

 this->PlayNote("C4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);
 this->PlayNote("G3",dur);

 this->PlayNote("O",dur);
 this->PlayNote("O",dur);
 this->PlayNote("E3",dur);
 this->PlayNote("O",dur);

 this->PlayNote("O",dur);
 this->PlayNote("A3",dur);
 this->PlayNote("O",dur);
 this->PlayNote("B3",dur);

 this->PlayNote("O",dur);
 this->PlayNote("AS3",dur);
 this->PlayNote("A3",dur);
 this->PlayNote("O",dur);

 this->PlayNote("G3",dur);
 this->PlayNote("E4",dur);
 this->PlayNote("G4",dur);

 this->PlayNote("A4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("F4",dur);
 this->PlayNote("G4",dur);

 this->PlayNote("O",dur);
 this->PlayNote("E4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("C4",dur);

 this->PlayNote("D4",dur);
 this->PlayNote("B3",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);

 this->PlayNote("C4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);
 this->PlayNote("G3",dur);

 this->PlayNote("O",dur);
 this->PlayNote("O",dur);
 this->PlayNote("E3",dur);
 this->PlayNote("O",dur);

 this->PlayNote("O",dur);
 this->PlayNote("A4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("B4",dur);

 this->PlayNote("O",dur);
 this->PlayNote("A4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);

 this->PlayNote("G3",dur);
 this->PlayNote("E4",dur);
 this->PlayNote("G4",dur);

 this->PlayNote("A4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("F4",dur);
 this->PlayNote("G4",dur);

 this->PlayNote("O",dur);
 this->PlayNote("E4",dur);
 this->PlayNote("O",dur);
 this->PlayNote("C4",dur);

 this->PlayNote("D4",dur);
 this->PlayNote("B3",dur);
 this->PlayNote("O",dur);
 this->PlayNote("O",dur);
         
        break;
 case NOKIA:
 this->PlayNote("E4",dur);

 this->PlayNote("D4",dur);
 this->PlayNote("F4",2*dur);
 this->PlayNote("G4",2*dur);
 this->PlayNote("C4",dur);

 this->PlayNote("B5",dur);
 this->PlayNote("D4",2*dur);
 this->PlayNote("E4",2*dur);
 this->PlayNote("B4",dur);

 this->PlayNote("A5",dur);
 this->PlayNote("C4",2*dur);
 this->PlayNote("E4",2*dur);
 this->PlayNote("A4",4*dur);
        break;

    }


}

void Speaker::PlayNote(char *note, long duration,int pause_dur){
    char Note[3];
    sprintf(Note,"%s",note);
    //Serial.println(Note);
    switch(Note[0]){
        case 'O' :
            delay(duration);
        break;
        case 'A' :
                switch(Note[1]){
                case '1':
                PlaySound(55, duration , pause_dur);
                break;
                case '2':
                PlaySound(110, duration , pause_dur);
                break;
                case '3':
                PlaySound(220, duration , pause_dur);
                break;
                case '4':
                PlaySound(440, duration , pause_dur);
                break;
                case '5':
                PlaySound(880, duration , pause_dur);
                break;
                case '6':
                PlaySound(1760, duration , pause_dur);
                break;
                case '7':
                PlaySound(3520, duration , pause_dur);
                break;
                case 'S':
                        switch(Note[2]){
                            case '1':
                                PlaySound(58, duration , pause_dur);
                                break;
                            case '2':
                                PlaySound(117, duration , pause_dur);
                                break;
                            case '3':
                                PlaySound(233, duration , pause_dur);
                                break;
                            case '4':
                                PlaySound(466, duration , pause_dur);
                                break;
                            case '5':
                                PlaySound(932, duration , pause_dur);
                                break;
                            case '6':
                                PlaySound(1865, duration , pause_dur);
                                break;
                            case '7':
                                PlaySound(3729, duration , pause_dur);
                                break;
                        }
                break;
                }
         break;
        case 'B' :
                switch(Note[1]){
                case '0':
                PlaySound(33, duration , pause_dur);
                break;
                case '1':
                PlaySound(62, duration , pause_dur);
                break;
                case '2':
                PlaySound(123, duration , pause_dur);
                break;
                case '3':
                PlaySound(247, duration , pause_dur);
                break;
                case '4':
                PlaySound(494, duration , pause_dur);
                break;
                case '5':
                PlaySound(988, duration , pause_dur);
                break;
                case '6':
                PlaySound(1976, duration , pause_dur);
                break;
                case '7':
                PlaySound(3951, duration , pause_dur);
                break;
                }
                break;
        case 'C' :
                switch(Note[1]){
                case '1':
                PlaySound(33, duration , pause_dur);
                break;
                case '2':
                PlaySound(65, duration , pause_dur);
                break;
                case '3':
                PlaySound(131, duration , pause_dur);
                break;
                case '4':
                PlaySound(262, duration , pause_dur);
                break;
                case '5':
                PlaySound(523, duration , pause_dur);
                break;
                case '6':
                PlaySound(1047, duration , pause_dur);
                break;
                case '7':
                PlaySound(2093, duration , pause_dur);
                break;
                case '8':
                PlaySound(4186, duration , pause_dur);
                break;
                case 'S':
                        switch(Note[2]){
                            case '1':
                                PlaySound(35, duration , pause_dur);
                                break;
                            case '2':
                                PlaySound(69, duration , pause_dur);
                                break;
                            case '3':
                                PlaySound(139, duration , pause_dur);
                                break;
                            case '4':
                                PlaySound(277, duration , pause_dur);
                                break;
                            case '5':
                                PlaySound(554, duration , pause_dur);
                                break;
                            case '6':
                                PlaySound(1109, duration , pause_dur);
                                break;
                            case '7':
                                PlaySound(2217, duration , pause_dur);
                                break;
                            case '8':
                                PlaySound(4435, duration , pause_dur);
                                break;
                        }
                break;
                }
                break;
        case 'D' :
                switch(Note[1]){
                case '1':
                PlaySound(37, duration , pause_dur);
                break;
                case '2':
                PlaySound(73, duration , pause_dur);
                break;
                case '3':
                PlaySound(147, duration , pause_dur);
                break;
                case '4':
                PlaySound(294, duration , pause_dur);
                break;
                case '5':
                PlaySound(587, duration , pause_dur);
                break;
                case '6':
                PlaySound(1175, duration , pause_dur);
                break;
                case '7':
                PlaySound(2349, duration , pause_dur);
                break;
                case '8':
                PlaySound(4699, duration , pause_dur);
                break;
                case 'S':
                        switch(Note[2]){
                            case '1':
                                PlaySound(39, duration , pause_dur);
                                break;
                            case '2':
                                PlaySound(78, duration , pause_dur);
                                break;
                            case '3':
                                PlaySound(156, duration , pause_dur);
                                break;
                            case '4':
                                PlaySound(311, duration , pause_dur);
                                break;
                            case '5':
                                PlaySound(622, duration , pause_dur);
                                break;
                            case '6':
                                PlaySound(1245, duration , pause_dur);
                                break;
                            case '7':
                                PlaySound(2489, duration , pause_dur);
                                break;
                            case '8':
                                PlaySound(4978, duration , pause_dur);
                                break;
                        }
                break;
                }
                break;
        case 'E' :
                switch(Note[1]){
                case '1':
                PlaySound(41, duration , pause_dur);
                break;
                case '2':
                PlaySound(82, duration , pause_dur);
                break;
                case '3':
                PlaySound(165, duration , pause_dur);
                break;
                case '4':
                PlaySound(330, duration , pause_dur);
                break;
                case '5':
                PlaySound(659, duration , pause_dur);
                break;
                case '6':
                PlaySound(1319, duration , pause_dur);
                break;
                case '7':
                PlaySound(2637, duration , pause_dur);
                break;
                }
                break;
         case 'F' :
                switch(Note[1]){
                case '1':
                PlaySound(44, duration , pause_dur);
                break;
                case '2':
                PlaySound(87, duration , pause_dur);
                break;
                case '3':
                PlaySound(175, duration , pause_dur);
                break;
                case '4':
                PlaySound(349, duration , pause_dur);
                break;
                case '5':
                PlaySound(698, duration , pause_dur);
                break;
                case '6':
                PlaySound(1397, duration , pause_dur);
                break;
                case '7':
                PlaySound(2794, duration , pause_dur);
                break;
                case 'S':
                        switch(Note[2]){
                            case '1':
                                PlaySound(46, duration , pause_dur);
                                break;
                            case '2':
                                PlaySound(93, duration , pause_dur);
                                break;
                            case '3':
                                PlaySound(185, duration , pause_dur);
                                break;
                            case '4':
                                PlaySound(370, duration , pause_dur);
                                break;
                            case '5':
                                PlaySound(740, duration , pause_dur);
                                break;
                            case '6':
                                PlaySound(1480, duration , pause_dur);
                                break;
                            case '7':
                                PlaySound(2960, duration , pause_dur);
                                break;
                        }
                break;
                }
                break;
         case 'G' :
                switch(Note[1]){
                case '1':
                PlaySound(49, duration , pause_dur);
                break;
                case '2':
                PlaySound(98, duration , pause_dur);
                break;
                case '3':
                PlaySound(196, duration , pause_dur);
                break;
                case '4':
                PlaySound(392, duration , pause_dur);
                break;
                case '5':
                PlaySound(784, duration , pause_dur);
                break;
                case '6':
                PlaySound(1568, duration , pause_dur);
                break;
                case '7':
                PlaySound(3136, duration , pause_dur);
                break;
                case 'S':
                        switch(Note[2]){
                            case '1':
                                PlaySound(52, duration , pause_dur);
                                break;
                            case '2':
                                PlaySound(104, duration , pause_dur);
                                break;
                            case '3':
                                PlaySound(208, duration , pause_dur);
                                break;
                            case '4':
                                PlaySound(415, duration , pause_dur);
                                break;
                            case '5':
                                PlaySound(831, duration , pause_dur);
                                break;
                            case '6':
                                PlaySound(1661, duration , pause_dur);
                                break;
                            case '7':
                                PlaySound(3322, duration , pause_dur);
                                break;
                        }
                break;
                }
                break;    
        default:break;
    }
}

int Speaker::GetID(){
    return(ID);
}