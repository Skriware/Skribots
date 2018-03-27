#include "SkriBot.h"


  SkriBot::SkriBot(String predef){
    NDistSensors    = 0;
    NLEDs           = 0;
    NLineSensors    = 0;
    NScopes         = 0;
    NLeftDCRotors   = 0;
    NRightDCRotors  = 0;
    NClaws          = 0;

    if(predef == "EDU_SHIELD"){
          AddDCRotor(EDU_ROTOR_SPEED_PIN_L,EDU_ROTOR_DIR_PIN_L,"Left");          //adding rotors for movement
          AddDCRotor(EDU_ROTOR_SPEED_PIN_R,EDU_ROTOR_DIR_PIN_R,"Right");
          AddDistSensor(EDU_ECHO_PIN_1,EDU_TRIG_PIN_1,1);   //adding Distance Sensors  and naming them "Left and Right";
          AddDistSensor(EDU_ECHO_PIN_2,EDU_TRIG_PIN_2,2);
          
          #ifndef _VARIANT_BBC_MICROBIT_
          AddClaw(EDU_CLAW_PIN1,EDU_CLAW_PIN2);
          #if DISABLED(DEBUG_MODE)
          AddLED(EDU_LED_DATA_PIN_1,1);
          AddLED(EDU_LED_DATA_PIN,0);
          #endif
          #endif
          AddLineSensor(EDU_LINE_SENSOR_1, 1);
          AddLineSensor(EDU_LINE_SENSOR_2, 2);
          AddLineSensor(EDU_LINE_SENSOR_3, 3);
          pinMode(EDU_BT_STATE_PIN,INPUT);
    }
   Stop();

  #ifndef _VARIANT_BBC_MICROBIT_
  Serial3.begin(9600);
  Serial3.setTimeout(50);
  #endif
  BLE_nameSetup();
  }

  char SkriBot::BLE_read(){
  char tmp;

  #ifdef _VARIANT_BBC_MICROBIT_
    BTLESerial.poll();
    tmp = BTLESerial.read();
  #else 
    tmp = Serial3.read();
  #endif
    return(tmp);
  }
  
  void SkriBot::BLE_write(char *msg){
  #ifdef _VARIANT_BBC_MICROBIT_
    BTLESerial.println(msg);
  #else 
    Serial3.println(msg);
  #endif
  }

  bool SkriBot::BLE_checkConnection(){
  bool connection;  
  #ifdef _VARIANT_BBC_MICROBIT_
     BTLESerial.poll();
     delay(1);
    connection = BTLESerial;
  #else 
    connection = digitalRead(EDU_BT_STATE_PIN) == HIGH;
  #endif
    return(connection);
  }

  int SkriBot::BLE_dataAvailable(){
    int dataAvalible;
  #ifdef _VARIANT_BBC_MICROBIT_
    BTLESerial.poll();
     if(BLE_checkConnection()){
    dataAvalible = BTLESerial.available();
  }else{
    dataAvalible = 0;
  }
  #else 
    dataAvalible = Serial3.available();
  #endif
    return(dataAvalible);

  }

  void SkriBot::BLE_nameSetup(){
    byte IfNamed = 0;
    #ifndef _VARIANT_BBC_MICROBIT_
    IfNamed = EEPROM.read(10);
    if(IfNamed != 1){
      char MAC[23] = {' '};
       delay(100);
       Serial3.write("AT");
       delay(100);
       Serial3.write("AT+ADDR?");
       delay(100);
       int MACCounter = 0;
       while(BLE_dataAvailable()){
        MAC[MACCounter] = Serial3.read();
        MACCounter++;
        if(MACCounter > 23)break;
       }
        char tmpmess[32] = {' '};
       sprintf(tmpmess,"AT+NAMESKRIBOT_%c%c%c",MAC[19],MAC[20],MAC[21]);
       delay(100);
       Serial3.write(tmpmess);
       delay(100);
       Serial3.write("AT+RESET");
       delay(100);
    }else{
      #ifdef DEBUG_MODE
      Serial.println("Robot named!");
      #endif
    }
    #else
    BTLESerial.setLocalName("SkriBotMini");
    BTLESerial.begin();
    ledMatrix.begin();
    #endif
  }

  void SkriBot::BLE_reset(){
       while(BLE_checkConnection()){
          #ifdef DEBUG_MODE
          Serial.println("waiting...");
          #endif
        }
       #ifndef _VARIANT_BBC_MICROBIT_
       EEPROM.write(10, 0);
       #endif
       BLE_nameSetup();
       
  }

  void SkriBot::sendNameInfo(){
    byte IfNamed = 0;

    #ifndef _VARIANT_BBC_MICROBIT_
    IfNamed = EEPROM.read(10);
    #endif
      if(IfNamed != 1){
        BLE_write("FALSE");
      }else{
        BLE_write("TRUE");
      }
  }
  void SkriBot::BLE_changeName(char name[], bool userConncection){
  while(BLE_checkConnection()){
    #ifdef DEBUG_MODE
    Serial.println("waiting...");
    #endif
  }
    #ifdef DEBUG_MODE
    Serial.println("disconnected!");
    #endif
  #ifdef _VARIANT_BBC_MICROBIT_
   BTLESerial.setLocalName(name);
   BTLESerial.begin();
   ledMatrix.begin();
  #else 
   char tmpmess[32];
   delay(100);
   Serial3.write("AT");
   delay(100);
   sprintf(tmpmess,"AT+NAME%s",name);
   Serial3.write(tmpmess);
   delay(100);
   Serial3.write("AT+RESET");
   delay(100);
   if(userConncection)EEPROM.write(10,1);
  #endif
  
  }

  void SkriBot::AddDCRotor(int SpeedPin,int DirectionPin, String Side){
    Rotor *dcrotor = new Rotor(SpeedPin,DirectionPin);
     if(Side == "Left"){
      LeftDCRotors[NLeftDCRotors] = dcrotor;
      NLeftDCRotors++;
     }else if(Side == "Right"){
      RightDCRotors[NRightDCRotors] = dcrotor;
      NRightDCRotors++;
     }
  }

  void SkriBot::AddDistSensor(int EchoPin,int TrigPin,String name){
    DistSensor *dsensor = new DistSensor(EchoPin,TrigPin,name);
    DistSensors[NDistSensors] = dsensor;
    NDistSensors++;
  }

  void SkriBot::AddDistSensor(int EchoPin,int TrigPin,int id){
    DistSensor *dsensor = new DistSensor(EchoPin,TrigPin,id);
    DistSensors[NDistSensors] = dsensor;
    NDistSensors++;
  }

  void SkriBot::AddLineSensor(int pinL,String Name){
    LineSensor *lsensor = new LineSensor(pinL,Name);
    LineSensors[NLineSensors] =  lsensor;
    NLineSensors++;
  }

  void SkriBot::AddLineSensor(int pinL,int id){
    LineSensor *lsensor = new LineSensor(pinL,id);
    LineSensors[NLineSensors] =  lsensor;
    NLineSensors++;
  }


    void SkriBot::AddDistSensor(String EDU_SHIELD_SLOT){
      if(EDU_SHIELD_SLOT == "D1"){
        AddDistSensor(EDU_ECHO_PIN_1,EDU_TRIG_PIN_1,"D1");  
      }else if(EDU_SHIELD_SLOT == "D2"){
        AddDistSensor(EDU_ECHO_PIN_2,EDU_TRIG_PIN_2,"D2");
      }
    }
    void SkriBot::AddLineSensor(String EDU_SHIELD_SLOT){
       if(EDU_SHIELD_SLOT == "L1"){
        AddLineSensor(EDU_LINE_SENSOR_1,"L1");
      }else if(EDU_SHIELD_SLOT == "L2"){
        AddLineSensor(EDU_LINE_SENSOR_2,"L2");
      }else if(EDU_SHIELD_SLOT == "L3" ){
        AddLineSensor(EDU_LINE_SENSOR_3,"L3");
      }
    }
    void SkriBot::AddDCRotor(String EDU_SHIELD_SLOT){
      if(EDU_SHIELD_SLOT == "LEFT"){
        AddDCRotor(EDU_ROTOR_SPEED_PIN_L,EDU_ROTOR_DIR_PIN_L,"Left");          
      }else if(EDU_SHIELD_SLOT == "RIGHT"){
        AddDCRotor(EDU_ROTOR_SPEED_PIN_R,EDU_ROTOR_DIR_PIN_R,"Right");
      }
    }
  

  #ifndef _VARIANT_BBC_MICROBIT_

  void SkriBot::AddClaw(int Claw_Pin, int Arm_Pin, byte id){
    Claw *claw = new Claw(Claw_Pin,Arm_Pin,id);
    Claws[NClaws] = claw;
    NClaws++;
  }
  void SkriBot::AddScope(int EchoPin,int Trigg,int ServoPin,String Name){
    Scope *scope = new Scope(EchoPin,Trigg,ServoPin,Name);
    Scopes[NScopes] = scope;
    NScopes++;
  }

   void SkriBot::AddLED(int pin,String name){
    RobotLED *led = new RobotLED(pin,name);
    LEDs[NLEDs] = led;
    NLEDs++;
  }

   void SkriBot::AddLED(int pin,int id){
    RobotLED *led = new RobotLED(pin,id);
    LEDs[NLEDs] = led;
    NLEDs++;
  }

   void SkriBot::AddLED(String EDU_SHIELD_SLOT){
      if(EDU_SHIELD_SLOT == "LED1"){
        AddLED(EDU_LED_DATA_PIN_1,"LED1");
      }else if(EDU_SHIELD_SLOT == "LED2"){
        AddLED(EDU_LED_DATA_PIN,"LED2");
      }
    }

  void SkriBot::SetScopeAngle(String name,int deg){
    for(int zz = 0; zz < NScopes ; zz++){
                    if(Scopes[zz]->GetName() == name){
                      Scopes[zz]->SetAngle(deg);
                      break;
                    }
      }
  }

  void SkriBot::AddClaw(){
        AddClaw(EDU_CLAW_PIN1,EDU_CLAW_PIN2);
    }    

  int SkriBot::GetScopeDistance(String name){
    for(int zz = 0; zz < NScopes ; zz++){
                    if(Scopes[zz]->GetName() == name){
                      return(Scopes[zz]->GetDistance());
                      break;
                    }
      }
  }

  #endif

   void SkriBot::CloseClaw(byte id){
         #ifndef _VARIANT_BBC_MICROBIT_
         for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Close();
                      break;
                    }
        }
        #endif
    }
    void SkriBot::OpenClaw(byte id){
       #ifndef _VARIANT_BBC_MICROBIT_
          for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Open();
                      break;
                    }
        }
        #endif
    }
    void SkriBot::Pick_Up(byte id){
       #ifndef _VARIANT_BBC_MICROBIT_
          for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Pick_Up();
                      break;
                    }
        }
        #endif
    }
    void SkriBot::Put_Down(byte id){
        #ifndef _VARIANT_BBC_MICROBIT_
          for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Put_Down();
                      break;
                    }
        }
        #endif
    }

   


  void SkriBot::TurnLEDOn(int R,int G, int B, String name){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(name == "ALL" || LEDs[zz]->GetName() == name){
                      LEDs[zz]->turnON(R,G,B);
                      if(name != "ALL")break;
                    }
      }
      #endif
  }

   void SkriBot::TurnLEDOff(String name){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(name == "ALL" || LEDs[zz]->GetName() == name){
                      LEDs[zz]->turnOFF();
                      if(name != "ALL")break;
                    }
      }
      #endif
  }

  void SkriBot::TurnLEDOn(int R,int G, int B, int _id){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(_id == -69 || LEDs[zz]->GetID() == _id){
                      LEDs[zz]->turnON(R,G,B);
                      if(_id != -69)break;
                    }
                  
      }
      delay(10);
      #endif
  }

  void SkriBot::TurnLEDOff(int _id){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(_id == -69 || LEDs[zz]->GetID() == _id){
                      LEDs[zz]->turnOFF();
                      if(_id != -69)break;
                    }
      }
      delay(10);
      #endif
  }

  int SkriBot::ReadLineSensor(String name){ 
    for(int zz = 0; zz < NLineSensors ; zz++){
                    if(LineSensors[zz]->GetName() == name){
                      return(LineSensors[zz]->ReadSensor());
                      break;
                    }
      }
    return(0);
  }

  int SkriBot::ReadLineSensor(int id){
     for(int zz = 0; zz < NLineSensors ; zz++){
                    if(LineSensors[zz]->GetID() == id){
                      return(LineSensors[zz]->ReadSensor());
                      break;
                    }
      }
      return(0);
  }


  int SkriBot::ReadDistSensor(int id, int max){
     for(int zz = 0; zz < NDistSensors ; zz++){
                    //Serial->print("Sensor:");
                    //Serial->println(DistSensors[zz]->GetID());
                    if(DistSensors[zz]->GetID() == id){
                      return(DistSensors[zz]->ReadSensor(max));
                      break;
                    }
      }
      return(0);
  }

   int SkriBot::ReadDistSensor(String name, int max){
     for(int zz = 0; zz < NDistSensors ; zz++){
                    //Serial->print("Sensor:");
                    //Serial->println(DistSensors[zz]->GetID());
                    if(DistSensors[zz]->GetName() == name){
                      return(DistSensors[zz]->ReadSensor(max));
                      break;
                    }
      }
      return(0);
  }



  
  void SkriBot::Move(char Dir,int ms){
      if (NLeftDCRotors  > 0 && NRightDCRotors  >0){
         switch(Dir){
        case 'B':
                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(0);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int zz = 0; zz < NRightDCRotors ; zz++){
                    RightDCRotors[zz]->SetDirection(0);
                    RightDCRotors[zz]->Move();
                  }
        break;
        
        case 'F':
                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->Move();
                  }
        break;

        case 'L':
                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(0);
                    RightDCRotors[kk]->Move();
                  }
         break;

         case 'R':
                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(0);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->Move();
                  }
         break;

        case 'S' :
                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->Stop();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->Stop();
                  }
         break; 
//*******************************************************************************
         case 'K' :
                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->Move();
                  }
         break;

         case 'Z' :
                    for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(0);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->SetSpeed(0.5*DCSpeed);
                    RightDCRotors[kk]->Move();
                  }
         break;

         case 'M' :
                   for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(0);
                    LeftDCRotors[kk]->SetSpeed(0.5*DCSpeed);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->Move();
                  }
         break;

      }
        
        if(ms > 0 ){
          delay(ms);
          for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetSpeed(DCSpeed);
                    LeftDCRotors[kk]->Stop();
                  }
          
           for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetSpeed(DCSpeed);
                    RightDCRotors[kk]->Stop();
            }
      }

    }
  }

  void SkriBot::RawRotorMove(int left, int right){
      byte leftDir,leftSpeed,rightDir,rightSpeed;

 
       if(left > 250){
        leftSpeed = left - 250;
        leftDir = 1;
      }else if(left == 250){
        leftSpeed = 0;
        leftDir = 1;
      }else{
        leftSpeed = 250 - left;
        leftDir = 0;
      }

        if(right > 250){
        rightSpeed = right-250;
        rightDir = 1;
      }else if(right == 250){
        rightSpeed = 0;
        rightDir = 1;
      }else{
        rightSpeed = 250-right;
        rightDir = 0;
      }



                for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(leftDir);
                    LeftDCRotors[kk]->SetSpeed(leftSpeed);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(rightDir);
                    RightDCRotors[kk]->SetSpeed(rightSpeed);
                    RightDCRotors[kk]->Move();
                  }
  }

    void SkriBot::SetSpeed(int s){ 
      DCSpeed = s;
      for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetSpeed(DCSpeed);
                    
                  }
          
      for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetSpeed(DCSpeed);
                    
            }
    }

    void SkriBot::TurnLeft(int ms){Move('Z',ms);}
    void SkriBot::TurnRight(int ms){Move('M',ms);}
    void SkriBot::FaceLeft(int ms){Move('L',ms);}
    void SkriBot::FaceRight(int ms){Move('R',ms);}
    void SkriBot::MoveForward(int ms){Move('F',ms);}
    void SkriBot::MoveBack(int ms){Move('B',ms);}
    void SkriBot::Stop(){Move('S',-1);}

   

