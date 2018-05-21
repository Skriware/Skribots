#include "Skribot.h"



  Skribot::Skribot(String predef){
    NDistSensors    = 0;
    NLEDs           = 0;
    NLineSensors    = 0;
    NScopes         = 0;
    NLeftDCRotors   = 0;
    NRightDCRotors  = 0;
    NClaws          = 0;
    connection_Break_Reported = false;
    using_BLE_Connection = false;
    Configure_Connections(predef);
  }

  void Skribot::Configure_Connections(String predef){
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
    }else if (predef == "SKRIBOT_MINI"){
           #ifdef _VARIANT_BBC_MICROBIT_
          AddDCRotor(SKRIBOT_MINI_SHILELD_MOTOR_1_DIR1_PIN,SKRIBOT_MINI_SHILELD_MOTOR_1_DIR2_PIN,"Left");
          AddDCRotor(SKRIBOT_MINI_SHILELD_MOTOR_2_DIR1_PIN,SKRIBOT_MINI_SHILELD_MOTOR_2_DIR2_PIN,"Right");
          AddLineSensor(SKRIBOT_MINI_SHILELD_SENSOR_0, 1);
          AddLineSensor(SKRIBOT_MINI_SHILELD_SENSOR_1, 2);
          AddLineSensor(SKRIBOT_MINI_SHILELD_SENSOR_2, 3);
          #endif
    }else if (predef == "EDU_SHIELD_NO_GRABBER"){
          AddDCRotor(EDU_ROTOR_SPEED_PIN_L,EDU_ROTOR_DIR_PIN_L,"Left");          //adding rotors for movement
          AddDCRotor(EDU_ROTOR_SPEED_PIN_R,EDU_ROTOR_DIR_PIN_R,"Right");
          AddDistSensor(EDU_ECHO_PIN_1,EDU_TRIG_PIN_1,1);   //adding Distance Sensors  and naming them "Left and Right";
          AddDistSensor(EDU_ECHO_PIN_2,EDU_TRIG_PIN_2,2);
          
          #ifndef _VARIANT_BBC_MICROBIT_
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
   SetSpeed(250);
   Stop();
  }

  char Skribot::BLE_read(){
  char tmp;

  #ifdef _VARIANT_BBC_MICROBIT_
    BTLESerial.poll();
    tmp = BTLESerial.read();
  #else 
    tmp = Serial3.read();
  #endif
    return(tmp);
  }
  
  void Skribot::BLE_write(char *msg){
  #ifdef _VARIANT_BBC_MICROBIT_
    BTLESerial.println(msg);
  #else 
    Serial3.println(msg);
  #endif
  }

  bool Skribot::BLE_checkConnection(){
  bool connection;  

  
  #ifdef _VARIANT_BBC_MICROBIT_
     //BTLESerial.poll();
     delay(1);
    connection = BTLESerial;
  #else 
    connection = digitalRead(EDU_BT_STATE_PIN) == HIGH;
  #endif
if(connection_Break_Reported){
    connection_Break_Reported = false;
    connection = false;
  }

    return(connection);
  }

  int Skribot::BLE_dataAvailable(){
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

  void Skribot::wait_And_Check_BLE_Connection(int ms,int interval){

    int loop_iterator = ms/interval;
    int ms_left_after_loop = loop_iterator%interval;
    delay(ms_left_after_loop);
    for(int yy = 1; yy < loop_iterator; yy++){
          if(using_BLE_Connection && !connection_Break_Reported && BLE_checkConnection() == false){
          connection_Break_Reported = true;
          break;
      }
      delay(interval);
    } 
    #ifdef DEBUG_MODE
    if(connection_Break_Reported)Serial.println("Connection LOST!");
    #endif
  }

  void Skribot::BLE_Setup(){

    #ifndef _VARIANT_BBC_MICROBIT_
    Serial3.begin(9600);
    Serial3.setTimeout(50);
    #endif

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
    Serial.begin(9600);
    BTLESerial.setLocalName("SkriBotMini");
    BTLESerial.begin();
    ledMatrix.begin();
    #endif

    using_BLE_Connection = true;
  }

  void Skribot::BLE_reset(){
       while(BLE_checkConnection()){
          #ifdef DEBUG_MODE
          Serial.println("waiting...");
          #endif
        }
       #ifndef _VARIANT_BBC_MICROBIT_
       EEPROM.write(10, 0);
       #endif
       BLE_Setup();
       
  }

  void Skribot::sendNameInfo(){
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
  void Skribot::BLE_changeName(char name[], bool userConncection){
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

  void Skribot::AddDCRotor(int SpeedPin,int DirectionPin, String Side){
    Rotor *dcrotor = new Rotor(SpeedPin,DirectionPin);
     if(Side == "Left"){
      LeftDCRotors[NLeftDCRotors] = dcrotor;
      NLeftDCRotors++;
     }else if(Side == "Right"){
      RightDCRotors[NRightDCRotors] = dcrotor;
      NRightDCRotors++;
     }
  }

  void Skribot::AddDistSensor(int EchoPin,int TrigPin,String name){
    DistSensor *dsensor = new DistSensor(EchoPin,TrigPin,name);
    DistSensors[NDistSensors] = dsensor;
    NDistSensors++;
  }

  void Skribot::AddDistSensor(int EchoPin,int TrigPin,int id){
    DistSensor *dsensor = new DistSensor(EchoPin,TrigPin,id);
    DistSensors[NDistSensors] = dsensor;
    NDistSensors++;
  }

  void Skribot::AddLineSensor(int pinL,String Name){
    LineSensor *lsensor = new LineSensor(pinL,Name);
    LineSensors[NLineSensors] =  lsensor;
    NLineSensors++;
  }

  void Skribot::AddLineSensor(int pinL,int id){
    LineSensor *lsensor = new LineSensor(pinL,id);
    LineSensors[NLineSensors] =  lsensor;
    NLineSensors++;
  }


    void Skribot::AddDistSensor(String EDU_SHIELD_SLOT){
      if(EDU_SHIELD_SLOT == "D1"){
        AddDistSensor(EDU_ECHO_PIN_1,EDU_TRIG_PIN_1,"D1");  
      }else if(EDU_SHIELD_SLOT == "D2"){
        AddDistSensor(EDU_ECHO_PIN_2,EDU_TRIG_PIN_2,"D2");
      }
    }
    void Skribot::AddLineSensor(String EDU_SHIELD_SLOT){
       if(EDU_SHIELD_SLOT == "L1"){
        AddLineSensor(EDU_LINE_SENSOR_1,"L1");
      }else if(EDU_SHIELD_SLOT == "L2"){
        AddLineSensor(EDU_LINE_SENSOR_2,"L2");
      }else if(EDU_SHIELD_SLOT == "L3" ){
        AddLineSensor(EDU_LINE_SENSOR_3,"L3");
      }
    }
    void Skribot::AddDCRotor(String EDU_SHIELD_SLOT){
      if(EDU_SHIELD_SLOT == "LEFT"){
        AddDCRotor(EDU_ROTOR_SPEED_PIN_L,EDU_ROTOR_DIR_PIN_L,"Left");          
      }else if(EDU_SHIELD_SLOT == "RIGHT"){
        AddDCRotor(EDU_ROTOR_SPEED_PIN_R,EDU_ROTOR_DIR_PIN_R,"Right");
      }
    }
  

  #ifndef _VARIANT_BBC_MICROBIT_

  void Skribot::AddClaw(int Claw_Pin, int Arm_Pin, byte id){
    Claw *claw = new Claw(Claw_Pin,Arm_Pin,id);
    Claws[NClaws] = claw;
    NClaws++;
  }
  void Skribot::AddScope(int EchoPin,int Trigg,int ServoPin,String Name){
    Scope *scope = new Scope(EchoPin,Trigg,ServoPin,Name);
    Scopes[NScopes] = scope;
    NScopes++;
  }

   void Skribot::AddLED(int pin,String name){
    RobotLED *led = new RobotLED(pin,name);
    LEDs[NLEDs] = led;
    NLEDs++;
  }

   void Skribot::AddLED(int pin,int id){
    RobotLED *led = new RobotLED(pin,id);
    LEDs[NLEDs] = led;
    NLEDs++;
  }

   void Skribot::AddLED(String EDU_SHIELD_SLOT){
      if(EDU_SHIELD_SLOT == "LED1"){
        AddLED(EDU_LED_DATA_PIN_1,"LED1");
      }else if(EDU_SHIELD_SLOT == "LED2"){
        AddLED(EDU_LED_DATA_PIN,"LED2");
      }
    }

  void Skribot::SetScopeAngle(String name,int deg){
    for(int zz = 0; zz < NScopes ; zz++){
                    if(Scopes[zz]->GetName() == name){
                      Scopes[zz]->SetAngle(deg);
                      break;
                    }
      }
  }

  void Skribot::AddClaw(){
        AddClaw(EDU_CLAW_PIN1,EDU_CLAW_PIN2);
    }    

  int Skribot::GetScopeDistance(String name){
    for(int zz = 0; zz < NScopes ; zz++){
                    if(Scopes[zz]->GetName() == name){
                      return(Scopes[zz]->GetDistance());
                      break;
                    }
      }
  }

  #endif

   void Skribot::CloseClaw(byte id){
         #ifndef _VARIANT_BBC_MICROBIT_
         for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Close();
                      break;
                    }
        }
        #endif
    }
    void Skribot::OpenClaw(byte id){
       #ifndef _VARIANT_BBC_MICROBIT_
          for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Open();
                      break;
                    }
        }
        #endif
    }
    void Skribot::Pick_Up(byte id){
       #ifndef _VARIANT_BBC_MICROBIT_
          for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Pick_Up();
                      break;
                    }
        }
        #endif
    }
    void Skribot::Put_Down(byte id){
        #ifndef _VARIANT_BBC_MICROBIT_
          for(int zz = 0; zz < NClaws ; zz++){
                    if(Claws[zz]->GetID() == id){
                      Claws[zz]->Put_Down();
                      break;
                    }
        }
        #endif
    }

   


  void Skribot::TurnLEDOn(int R,int G, int B, String name){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(name == "ALL" || LEDs[zz]->GetName() == name){
                      LEDs[zz]->turnON(R,G,B);
                      if(name != "ALL")break;
                    }
      }
      #endif
  }

   void Skribot::TurnLEDOff(String name){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(name == "ALL" || LEDs[zz]->GetName() == name){
                      LEDs[zz]->turnOFF();
                      if(name != "ALL")break;
                    }
      }
      #endif
  }

  void Skribot::TurnLEDOn(int R,int G, int B, int _id){
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

  void Skribot::TurnLEDOff(int _id){
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

  int Skribot::ReadLineSensor(String name){ 
    for(int zz = 0; zz < NLineSensors ; zz++){
                    if(LineSensors[zz]->GetName() == name){
                      return(LineSensors[zz]->ReadSensor());
                      break;
                    }
      }
    return(0);
  }

  int Skribot::ReadLineSensor(int id){
     for(int zz = 0; zz < NLineSensors ; zz++){
                    if(LineSensors[zz]->GetID() == id){
                      return(LineSensors[zz]->ReadSensor());
                      break;
                    }
      }
      return(0);
  }


  int Skribot::ReadDistSensor(int id, int max){
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

   int Skribot::ReadDistSensor(String name, int max){
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

  
  void Skribot::Move(char Dir,int ms){
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
          wait_And_Check_BLE_Connection(ms,10);
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

  void Skribot::RawRotorMove(int left, int right){
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

                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(rightDir);
                    RightDCRotors[kk]->SetSpeed(rightSpeed);
                    RightDCRotors[kk]->Move();
                  }
                   for(int yy = 0; yy < NLeftDCRotors ; yy++){
                    LeftDCRotors[yy]->SetDirection(leftDir);
                    LeftDCRotors[yy]->SetSpeed(leftSpeed);
                    LeftDCRotors[yy]->Move();
                  }

                
               
          
                
  }

    void Skribot::SetSpeed(int s){ 
      DCSpeed = s;
      for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetSpeed(DCSpeed);
                    
                  }
          
      for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetSpeed(DCSpeed);
                    
            }
    }

    void Skribot::TurnLeft(int ms){Move('Z',ms);}
    void Skribot::TurnRight(int ms){Move('M',ms);}
    void Skribot::FaceLeft(int ms){Move('L',ms);}
    void Skribot::FaceRight(int ms){Move('R',ms);}
    void Skribot::MoveForward(int ms){Move('F',ms);}
    void Skribot::MoveBack(int ms){Move('B',ms);}
    void Skribot::Stop(){Move('S',-1);}

   

