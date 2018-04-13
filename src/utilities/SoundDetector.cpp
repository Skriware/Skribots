#include "SoundDetector.h"

int SoundDetector::Nsignal = 0;
long SoundDetector::times[5] = {0,0,0,0,0};

SoundDetector::SoundDetector(int outputPin, String name){
	 _out_pin = outputPin;
  	 _name	  = name;
  	 pinMode(_out_pin,INPUT);
  	 attachInterrupt(digitalPinToInterrupt(_out_pin),SoundDetected, RISING);
  	 interrupts();

}

String SoundDetector::name(){
	return(_name);
}

void SoundDetector::SoundDetected(){
	long tmp = millis();
	if(abs(tmp - times[SoundDetector::Nsignal])  > 100){
		SoundDetector::Nsignal++;
		if(Nsignal > 4){
			SoundDetector::Nsignal = 0;
		}
		SoundDetector::times[SoundDetector::Nsignal] = tmp;
		for(int i = 0 ; i < 5 ; i++)
		Serial.println(times[i]);
	}
}

int SoundDetector::CountSound(int sec){
	/*int sounds = 0;
	int diftimes[5];
	diftimes[0] = abs(times[0] - times[5]);
	times[0] = 0;
	for(int i = 1 ; i < 4 ; i++){
		diftimes[i] = abs(times[i] - times[i+i]);
		times[i] = 0;

	}
	for(int t = 0; t <5 ;t++){
		if(diftimes[t] < sec) sounds++;
	}

	return(sounds);
	*/
	return(0);
}