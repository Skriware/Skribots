#include "Skribot.h"

#define EEPROM_EMPTY_ESP32 255
#define EEPROM_EMPTY_ARDUINO 0

  bool Skribot::EEPROM_EMPTY(int val){
    return(val == EEPROM_EMPTY_ESP32 || val == EEPROM_EMPTY_ARDUINO);
  }

  Skribot::Skribot(String predef){
    NDistSensors    = 0;
    NLEDs           = 0;
    NLineSensors    = 0;
    NScopes         = 0;
    NLeftDCRotors   = 0;
    NRightDCRotors  = 0;
    NClaws          = 0;
    BTmodule = NULL;
    SPIcomm[0] = NULL;
    SPIcomm[1] = NULL;
    using_BLE_Connection = false;
    program_End_Reported = false;
    stausLEDused = false;
    high_power_usage = false;
    claw_closed = false;
    claw_closed_time = true;
    config_mode = false;
    Remote_block_used = false;
    Configure_Connections(predef);
    #ifdef DEBUG_MODE
    Serial.begin(115200);
    #endif
  }
  void Skribot::Configure_Connections(String predef){
    #ifndef ESP_H
    if(predef == "EDU_SHIELD"){
          AddDCRotor(EDU_ROTOR_SPEED_PIN_L,EDU_ROTOR_DIR_PIN_L,"Left");          //adding rotors for movement
          AddDCRotor(EDU_ROTOR_SPEED_PIN_R,EDU_ROTOR_DIR_PIN_R,"Right");
          Stop();
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
          status = new StatusLED(EDU_SHIELD_STATUS_LED_R_PIN,EDU_SHIELD_STATUS_LED_G_PIN,EDU_SHIELD_STATUS_LED_B_PIN,EDU_SHILED_POWER_READOUT_PIN);
          stausLEDused = true;
          BLE_Set_Module(HM_10);
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
          BLE_Set_Module(HM_10);
    }
    #else
    if(predef == "SKRIBRAIN"){
          AddDCRotor(SKRIBRAIN_MOTOR_L_DIR2_PIN,SKRIBRAIN_MOTOR_L_DIR1_PIN,"Left");
          AddDCRotor(SKRIBRAIN_MOTOR_R_DIR2_PIN,SKRIBRAIN_MOTOR_R_DIR1_PIN,"Right");
          AddLED(SKRIBRAIN_LED_PIN_2,1);
          AddLED(SKRIBRAIN_LED_PIN_1,0);
          AddDistSensor(SKRIBRAIN_ECHO_PIN_1,SKRIBRAIN_TRIG_PIN_1,1);   
          AddDistSensor(SKRIBRAIN_ECHO_PIN_2,SKRIBRAIN_TRIG_PIN_2,2);
          AddLineSensor(LINE_PIN_1, 1);
          AddLineSensor(LINE_PIN_2, 2);
          AddLineSensor(LINE_PIN_3, 3);
          AddClaw(SKRIBRAIN_SERVO_PIN_1,SKRIBRAIN_SERVO_PIN_2);
          BLE_Set_Module(ESP32_BLE); 
          status = new StatusLED(SKRIBRAIN_STATUS_LED_PIN,SKRIBRAIN_SERVO_PIN_3);
          stausLEDused = true;
        }else if(predef == "SKRIBRAIN+LED_MATRIX"){ 
          AddDCRotor(SKRIBRAIN_MOTOR_L_DIR2_PIN,SKRIBRAIN_MOTOR_L_DIR1_PIN,"Left");
          AddDCRotor(SKRIBRAIN_MOTOR_R_DIR2_PIN,SKRIBRAIN_MOTOR_R_DIR1_PIN,"Right");
          AddLED(SKRIBRAIN_LED_PIN_2,1);
          AddDistSensor(SKRIBRAIN_ECHO_PIN_1,SKRIBRAIN_TRIG_PIN_1,1);   
          AddDistSensor(SKRIBRAIN_ECHO_PIN_2,SKRIBRAIN_TRIG_PIN_2,2);
          AddLineSensor(LINE_PIN_1, 1);
          AddLineSensor(LINE_PIN_2, 2);
          AddLineSensor(LINE_PIN_3, 3);
          AddClaw(SKRIBRAIN_SERVO_PIN_1,SKRIBRAIN_SERVO_PIN_2);
          BLE_Set_Module(ESP32_BLE); 
          status = new StatusLED(SKRIBRAIN_STATUS_LED_PIN,SKRIBRAIN_SERVO_PIN_3);
          stausLEDused = true;
          Add_Mono_LED_matrix(SPI_PORT_2);
        }
    #endif
   SetSpeed(250);
   Stop();
  }

  void Skribot::ConfigureBoardEEPROM(){
   
      #ifdef DEBUG_MODE
          Serial.println("Checking EEPROM...");
      #endif
       #ifdef ESP_H
       if(!EEPROM.begin(64)){
          #ifdef DEBUG_MODE
          Serial.println("EEPROM init fail, aborting EEPROM check.");
          #endif
          return;
       }
      #endif
       Board_type = EEPROM.read(EEPROM_BOARD_VERSION_ADDR);
       if(EEPROM_EMPTY(Board_type)){                                   //No board Version defined
        EEPROM.write(EEPROM_BOARD_VERSION_ADDR,BOARD_VERSION);
        Board_type = BOARD_VERSION;                             //Asigning Board Version to the newest one.
         #ifdef ESP_H 
              EEPROM.commit(); 
         #endif 
        #ifdef DEBUG_MODE
          Serial.println("First time flash detected");
          #endif
        return;
       }
       delay(10);                                              //EEPROM delay in order to avoid EEPROM ERRORS
       byte userChange = EEPROM.read(EEPROM_SETTINGS_OVERRIDED_ADDR);
       delay(10);
       if(EEPROM_EMPTY(userChange)){
         #ifdef DEBUG_MODE
          Serial.println("No user Settings in EEPROM Configuration");
          #endif
          user_config = false;
        return;                                                                         //No user change done aborting the process;
       }else if(userChange == 1){
       user_config = true;
       delay(10);                                              //EEPROM delay in order to avoid EEPROM ERRORS
       byte left_invert = EEPROM.read(EEPROM_LEFT_INVERT_ADDR);
       delay(10);                                              //EEPROM delay in order to avoid EEPROM ERRORS
       byte right_invert = EEPROM.read(EEPROM_RIGHT_INVERT_ADDR);
       delay(10);                                              //EEPROM delay in order to avoid EEPROM ERRORS
       byte left_scale = EEPROM.read(EEPROM_LEFT_SCALE_ADDR);
       delay(10); 
       byte right_scale = EEPROM.read(EEPROM_RIGHT_SCALE_ADDR);
       delay(10);                                             //EEPROM delay in order to avoid EEPROM ERRORS
       int L1_b = Read_EEPROM_INT(EEPROM_L1_BORDER_ADDR);
       delay(10);                                              //EEPROM delay in order to avoid EEPROM ERRORS
       int L2_b = Read_EEPROM_INT(EEPROM_L2_BORDER_ADDR);
       delay(10);                                             //EEPROM delay in order to avoid EEPROM ERRORS
       int L3_b = Read_EEPROM_INT(EEPROM_L3_BORDER_ADDR);
       delay(10);

       Set_Line_Sensor_Logic_Border(L1_b,L2_b,L3_b);
       if(!EEPROM_EMPTY(right_invert))Invert_Right_Rotors(right_invert);
       if(!EEPROM_EMPTY(left_invert))Invert_Left_Rotors(left_invert);
       if(!EEPROM_EMPTY(left_scale))Scale_Left_Rotors(left_scale);
       if(!EEPROM_EMPTY(right_scale))Scale_Right_Rotors(right_scale);

      #ifdef DEBUG_MODE
      Serial.println("User Corrections:");
      Serial.print("LS: ");
      Serial.println(left_scale);
      Serial.print("RS: ");
      Serial.println(right_scale);
      Serial.print("LI: ");
      Serial.println(left_invert);
      Serial.print("RI: ");
      Serial.println(right_invert);
      Serial.println(L1_b);
      Serial.println(L2_b); 
      Serial.println(L3_b);
      #endif

       }else{
        #ifdef DEBUG_MODE
        Serial.println("Unexpected user cofig value:");
        Serial.println(userChange);
        #endif
       }
   
  }

  void Skribot::Write_EEPROM_INT(byte addr,int value){
      EEPROM.write(addr,value);
      #ifdef ESP_H 
 EEPROM.commit(); 
 #endif
      delay(100);
      EEPROM.write(addr+1,value>>8);
      #ifdef ESP_H 
 EEPROM.commit(); 
 #endif
  }

  int Skribot::Read_EEPROM_INT(byte addr){
        int b3 = 0;
        int b1 =  EEPROM.read(addr+1);
        delay(10);
        int b2  = EEPROM.read(addr);
      if(EEPROM_EMPTY(b1)&& EEPROM_EMPTY(b2)){
        b3 = 0;
      }else{
        b3 = b2 | (int(b1) << 8);
      }
    return(b3);
  }

  char Skribot::BLE_read(){
  char tmp;

  #ifdef _VARIANT_BBC_MICROBIT_
    BTLESerial.poll();
    tmp = BTLESerial.read();
  #else 
   tmp = BTmodule->BLE_read();
  #endif
    return(tmp);
  }
  
  void Skribot::BLE_write(char *msg){
  #ifdef _VARIANT_BBC_MICROBIT_
    BTLESerial.println(msg);
  #else 
    BTmodule->BLE_write(msg);
  #endif
  }

  bool Skribot::BLE_checkConnection(){
  bool connection;  
  #ifdef _VARIANT_BBC_MICROBIT_
    connection = BTLESerial;
  #else 
   connection = BTmodule->BLE_checkConnection();
  #endif
if(connection_Break_Reported){
    connection_Break_Reported = false;
    connection = false;
  }
if(claw_closed && (millis() - claw_closed_time > 180000)){
      #ifdef DEBUG_MODE
       Serial.println("Program ended due to too long claw in closed state!");
      #endif
      OpenClaw();
      program_End_Reported = true;
      #ifdef ESP_H
      status->TurnOn(OFF,2);
      delay(200);
      status->TurnOn(RED,2);
      delay(200);
      status->TurnOn(OFF,2);
      delay(200);
      status->TurnOn(RED,2);
      delay(200);
      #endif
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
    dataAvalible = BTmodule->BLE_dataAvailable();
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
        }else if(using_BLE_Connection && !program_End_Reported && BLE_dataAvailable() > 0){
            char tmp;
            while(BLE_dataAvailable() > 0){
              tmp = BLE_read();
              delay(5);                     // to be sure that next char will be recieved
              if((tmp == 'E' && BLE_read() == 'N' && BLE_read() == 'D') || (tmp == 'B' && BLE_read() == 'E' && BLE_read() == 'G')){
                program_End_Reported = true;
              }
              #ifndef ESP_H && _VARIANT_BBC_MICROBIT_
              if(tmp != 'B')serialFlush();
              #endif
            }
            if(program_End_Reported || connection_Break_Reported)break;
          
      }
      if(stausLEDused)BaterryCheck();
      delay(interval);
    } 
    #ifdef DEBUG_MODE
    if(connection_Break_Reported)Serial.println("Connection LOST!");
    #endif
  }

  bool Skribot::ProgramENDRepotred(){
    
    if(program_End_Reported){
      program_End_Reported = false;
      return(true);
    }else{
      return(false);
    }

    return(program_End_Reported);
  }


  void Skribot::BLE_Setup(){
    #ifndef _VARIANT_BBC_MICROBIT_
    BTmodule = new BLEModule(BLE_MODULE_TYPE);
    BTmodule->BLE_Setup();
    #else
    Serial.begin(9600);
    BTLESerial.setLocalName("SkriBotMini");
    BTLESerial.begin();
    ledMatrix.begin();
    #endif
    using_BLE_Connection = true;
  }
   void Skribot::BLE_Set_Module(moduleType type){
          BLE_MODULE_TYPE = type;
   }

  void Skribot::BLE_reset(){
       while(BLE_checkConnection()){
          #ifdef DEBUG_MODE
          Serial.println("waiting...");
          #endif
        }
        #ifdef ESP_H
      BTmodule->BLE_reset();
        #else
       BLE_Setup();
       #endif
       
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
    BTmodule->BLE_changeName(name);
    ESP.restart();
  
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

  void Skribot::AddLightSensor(int pinL,int id){
    LightSensor *lsensor = new LightSensor(pinL,id);
    LightSensors[NLightSensors] =  lsensor;
    NLightSensors++;
  }


  void Skribot::AddLineSensor(int pinL,int id){
    LineSensor *lsensor = new LineSensor(pinL,id);
    LineSensors[NLineSensors] =  lsensor;
    NLineSensors++;
  }


#ifndef _VARIANT_BBC_MICROBIT_
      
    void Skribot::AddDistSensor(String SHIELD_SLOT){
      #ifndef ESP_H 
      if(SHIELD_SLOT == "D1"){
        AddDistSensor(EDU_ECHO_PIN_1,EDU_TRIG_PIN_1,"D1");  
      }else if(SHIELD_SLOT == "D2"){
        AddDistSensor(EDU_ECHO_PIN_2,EDU_TRIG_PIN_2,"D2");
      }
      #else
       if(SHIELD_SLOT == "D1"){
        AddDistSensor(SKRIBRAIN_ECHO_PIN_1,SKRIBRAIN_TRIG_PIN_1,"D1");  
      }else if(SHIELD_SLOT == "D2"){
        AddDistSensor(SKRIBRAIN_ECHO_PIN_2,SKRIBRAIN_TRIG_PIN_2,"D2");
      }
      #endif
    }
    void Skribot::AddLineSensor(String SHIELD_SLOT){
      #ifndef ESP_H 
       if(SHIELD_SLOT == "L1"){
        AddLineSensor(EDU_LINE_SENSOR_1,"L1");
      }else if(SHIELD_SLOT == "L2"){
        AddLineSensor(EDU_LINE_SENSOR_2,"L2");
      }else if(SHIELD_SLOT == "L3" ){
        AddLineSensor(EDU_LINE_SENSOR_3,"L3");
      }
      #else
      if(SHIELD_SLOT == "L1"){
        AddLineSensor(SKRIBRAIN_ANALOG_PIN_1,"L1");
      }else if(SHIELD_SLOT == "L2"){
        AddLineSensor(SKRIBRAIN_ANALOG_PIN_2,"L2");
      }else if(SHIELD_SLOT == "L3" ){
        AddLineSensor(SKRIBRAIN_ANALOG_PIN_3,"L3");
      }
      #endif
    }
    void Skribot::AddDCRotor(String SHIELD_SLOT){
      #ifndef ESP_H 
      if(SHIELD_SLOT == "LEFT"){
        AddDCRotor(EDU_ROTOR_SPEED_PIN_L,EDU_ROTOR_DIR_PIN_L,"Left");          
      }else if(SHIELD_SLOT == "RIGHT"){
        AddDCRotor(EDU_ROTOR_SPEED_PIN_R,EDU_ROTOR_DIR_PIN_R,"Right");
      }
      #else
       if(SHIELD_SLOT == "LEFT"){
        AddDCRotor(SKRIBRAIN_MOTOR_L_DIR2_PIN,SKRIBRAIN_MOTOR_L_DIR1_PIN,"Left");          
      }else if(SHIELD_SLOT == "RIGHT"){
        AddDCRotor(SKRIBRAIN_MOTOR_R_DIR2_PIN,SKRIBRAIN_MOTOR_R_DIR1_PIN,"Right");
      }
      #endif
    }
   void Skribot::AddLED(String SHIELD_SLOT){
    #ifndef ESP_H 
      if(SHIELD_SLOT == "LED1"){
        AddLED(EDU_LED_DATA_PIN_1,"LED1");
      }else if(SHIELD_SLOT == "LED2"){
        AddLED(EDU_LED_DATA_PIN,"LED2");
      }
      #else
      if(SHIELD_SLOT == "LED1"){
        AddLED(SKRIBRAIN_LED_PIN_1,"LED1");
      }else if(SHIELD_SLOT == "LED2"){
        AddLED(SKRIBRAIN_LED_PIN_2,"LED2");
      }
      #endif
    }

     void Skribot::AddClaw(){
      #ifndef ESP_H 
        AddClaw(EDU_CLAW_PIN1,EDU_CLAW_PIN2);
      #else
        AddClaw(SKRIBRAIN_SERVO_PIN_1,SKRIBRAIN_SERVO_PIN_2);
      #endif
    } 

    void Skribot::AddDistSensor(byte SHIELD_SLOT){
          #ifdef ESP_H 
    if(SHIELD_SLOT == D1_PORT){
        AddDistSensor(SKRIBRAIN_ECHO_PIN_1,SKRIBRAIN_TRIG_PIN_1,D1_PORT);  
    }else if(SHIELD_SLOT == D2_PORT){
        AddDistSensor(SKRIBRAIN_ECHO_PIN_2,SKRIBRAIN_TRIG_PIN_2,D2_PORT);
    }
          #endif
    }

    void Skribot::ConfigureSPIHandler(byte SPI_PORT){
    
    }

  void Skribot::Add_Mono_LED_matrix(byte SPI_PORT){
    if(SPI_PORT <2){
      SPIcomm[SPI_PORT] = new SPIHandler(SPI_PORT);
      LED_Matrixes[SPI_PORT] = new Mono_LED_Matrix(SPIcomm[SPI_PORT]);
    }
    SPIcomm[SPI_PORT]->set_SPI_Settings(4000000, MSBFIRST, SPI_MODE0);
    SPIcomm[SPI_PORT]->set_SPI_bit_format(16);

    LED_Matrixes[SPI_PORT]->Init();
    LED_Matrixes[SPI_PORT]->SetIntensity(8);
    LED_Matrixes[SPI_PORT]->Update();

         
  }
  void Skribot::AddBuzzer(byte BUZZER_PIN){
          
  #ifdef ESP_H 
    if(BUZZER_PIN == SERVO_1){
        Buzzers[SERVO_1] = new Buzzer(SKRIBRAIN_SERVO_PIN_1);
    }else if(BUZZER_PIN == SERVO_2){
        Buzzers[SERVO_2] = new Buzzer(SKRIBRAIN_SERVO_PIN_2); 
    }
  #else
    Buzzers[0] = new Buzzer(13);
  #endif

}

#endif
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

   void Skribot::AddLED(int pin,String name,byte N_LED){
    RobotLED *led = new RobotLED(pin,name,N_LED);
    LEDs[NLEDs] = led;
    NLEDs++;
  }

   void Skribot::AddLED(int pin,int id,byte N_LED){
    RobotLED *led = new RobotLED(pin,id,N_LED);
    LEDs[NLEDs] = led;
    NLEDs++;
  }

  void Skribot::SetScopeAngle(String name,int deg){
    for(int zz = 0; zz < NScopes ; zz++){
                    if(Scopes[zz]->GetName() == name){
                      Scopes[zz]->SetAngle(deg);
                      break;
                    }
      }
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
                      high_power_usage = true;
                      claw_closed = true;
                      claw_closed_time = millis();
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
                      high_power_usage = false;
                      claw_closed = false;
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
                      high_power_usage = true;
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
                      high_power_usage = false;
                      break;
                    }
        }
        #endif
    }

   
  void Skribot::TurnLEDOn(int R,int G, int B, String name,byte N_LED){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(name == "ALL" || LEDs[zz]->GetName() == name){
                      LEDs[zz]->turnON(R,G,B,N_LED);
                      if(name != "ALL")break;
                    }
      }
      #endif
  }

   void Skribot::TurnLEDOff(String name,byte N_LED){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(name == "ALL" || LEDs[zz]->GetName() == name){
                      LEDs[zz]->turnOFF(N_LED);
                      
                      if(name != "ALL")break;
                    }
      }
      #endif
  }

  void Skribot::TurnLEDOn(int R,int G, int B, int _id,byte N_LED){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(_id == -69 || LEDs[zz]->GetID() == _id){
                      LEDs[zz]->turnON(R,G,B,N_LED);
                      if(_id != -69)break;
                    }                
      }
   
      #endif
  }

  void Skribot::TurnLEDOff(int _id, byte N_LED){
    #ifndef _VARIANT_BBC_MICROBIT_
    for(int zz = 0; zz < NLEDs ; zz++){
                    if(_id == -69 || LEDs[zz]->GetID() == _id){
                      LEDs[zz]->turnOFF(N_LED);
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
                    if(DistSensors[zz]->GetID() == id){
                      return(DistSensors[zz]->ReadSensor(max));
                      break;
                    }
      }
      return(0);
  }

   int Skribot::ReadDistSensor(String name, int max){
     for(int zz = 0; zz < NDistSensors ; zz++){
                    if(DistSensors[zz]->GetName() == name){
                      return(DistSensors[zz]->ReadSensor(max));
                      break;
                    }
      }
      return(0);
  }

    void Skribot::Set_Line_Sensor_Logic_Border(int L1_border,int L2_border,int L3_border){
      for(int zz = 0; zz < NLineSensors ; zz++){
                    if(LineSensors[zz]->GetSensorPin() == LINE_PIN_1 && L1_border != 0){
                      LineSensors[zz]->SetLogicBorder(L1_border);
                    }else if(LineSensors[zz]->GetSensorPin() == LINE_PIN_2 && L2_border != 0){
                      LineSensors[zz]->SetLogicBorder(L2_border);
                    }else if(LineSensors[zz]->GetSensorPin() == LINE_PIN_3 && L3_border != 0){
                      LineSensors[zz]->SetLogicBorder(L3_border);
                    }
      }
    }

    void Skribot::Invert_Left_Rotors(bool inv){
       for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->invert_rotor(inv);
                  }
    }
    
    void Skribot::Invert_Right_Rotors(bool inv){
       for(int zz = 0; zz < NRightDCRotors ; zz++){
                    RightDCRotors[zz]->invert_rotor(inv);
                  }
    }

  
     void Skribot::Scale_Left_Rotors(byte scale){
       for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->scale_speed(scale);
                  }
    }
    
    void Skribot::Scale_Right_Rotors(byte scale){
       for(int zz = 0; zz < NRightDCRotors ; zz++){
                    RightDCRotors[zz]->scale_speed(scale);
                  }
    }

  void Skribot::Move(char Dir,int ms){
      if (NLeftDCRotors  > 0 && NRightDCRotors  >0){
         switch(Dir){
        case 'B':
                  for(int zz = 0; zz < NRightDCRotors ; zz++){
                    RightDCRotors[zz]->SetDirection(0);
                    RightDCRotors[zz]->Move();
                  }

                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(0);
                    LeftDCRotors[kk]->Move();
                  }
        break;
        
        case 'F':
                  
                  for(int zz = 0; zz < NRightDCRotors ; zz++){
                    RightDCRotors[zz]->SetDirection(1);
                    RightDCRotors[zz]->Move();
                  }

                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->Move();
                  }
        break;

        case 'R':
                  for(int zz = 0; zz < NLeftDCRotors ; zz++){
                    LeftDCRotors[zz]->SetDirection(1);
                    LeftDCRotors[zz]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(0);
                    RightDCRotors[kk]->Move();
                  }
         break;

         case 'L':
                  for(int zz = 0; zz < NLeftDCRotors ; zz++){
                    LeftDCRotors[zz]->SetDirection(0);
                    LeftDCRotors[zz]->Move();
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
                  high_power_usage = false;
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
                    LeftDCRotors[kk]->SetDirection(1);
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
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->SetSpeed(0.5*DCSpeed);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->Move();
                  }
         break;

      } 
      if(Dir != 'S')high_power_usage = true;
        if(ms > 0 ){
          wait_And_Check_BLE_Connection(ms,10);
          for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->Stop();
                  }
          
           for(int k = 0; k < NRightDCRotors ; k++){
                    RightDCRotors[k]->Stop();
            }
            high_power_usage=false;
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
        leftDir = 0;
      }else{
        leftSpeed = 250 - left;
        leftDir = 0;
      }

      if(right > 250){
        rightSpeed = right-250;
        rightDir = 1;
      }else if(right == 250){
        rightSpeed = 0;
        rightDir = 0;
      }else{
        rightSpeed = 250-right;
        rightDir = 0;
      }
                  if(right == 250){
                    for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->Stop();
                    }
                  }else{
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(rightDir);
                    RightDCRotors[kk]->SetSpeed(rightSpeed);
                    RightDCRotors[kk]->Move();
                  }
                  }
                  if(left == 250){
                    for(int kk = 0; kk < NLeftDCRotors ; kk++){
                      LeftDCRotors[kk]->Stop();
                    }
                  }else{
                   for(int yy = 0; yy < NLeftDCRotors ; yy++){
                    LeftDCRotors[yy]->SetDirection(leftDir);
                    LeftDCRotors[yy]->SetSpeed(leftSpeed);
                    LeftDCRotors[yy]->Move();
                  }
                  }
                  if (rightSpeed != 0 && leftSpeed != 0){
                    high_power_usage = true;
                  }else{
                    high_power_usage = false;
  }
}

    void Skribot::SetSpeed(int s){ 
      DCSpeed = s;
      for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetSpeed(DCSpeed);
                    
                  }
          
      for(int jj = 0; jj < NRightDCRotors ; jj++){
                    RightDCRotors[jj]->SetSpeed(DCSpeed);
                    
            }
    }

    void Skribot::TurnLeft(int ms){Move('Z',ms);}
    void Skribot::TurnRight(int ms){Move('M',ms);}
    void Skribot::FaceLeft(int ms){Move('L',ms);}
    void Skribot::FaceRight(int ms){Move('R',ms);}
    void Skribot::MoveForward(int ms){Move('F',ms);}
    void Skribot::MoveBack(int ms){Move('B',ms);}
    void Skribot::Stop(){Move('S',-1);}

  int Skribot::LightSensor_Raw(int id){
    int output;
    for(int zz = 0; zz < NLightSensors ; zz++){
                    if(LightSensors[zz]->GetID() == id){
                      output = LightSensors[zz]->ReadRaw();
                      break;
                    }
                  
      }
      return(output);
     }
    bool Skribot::LightSensor_Dark(int id){
          bool output;
    for(int zz = 0; zz < NLightSensors ; zz++){
                    if(LightSensors[zz]->GetID() == id){
                      output = LightSensors[zz]->isDark();
                      break;
                    }
                  
      }
      return(output);
    }
    bool Skribot::LightSensor_Bright(int id){
          bool output;
    for(int zz = 0; zz < NLightSensors ; zz++){
                    if(LightSensors[zz]->GetID() == id){
                      output = LightSensors[zz]->isBright();
                      break;
                    }
                  
      }
      return(output);
    }

    int Skribot::BaterryCheck(){
      int tmpStatus;
      if(stausLEDused && !high_power_usage){
        tmpStatus = status->CheckBateryStatus();
      }else{
        tmpStatus = 0;
      }
      return(tmpStatus);
    }

    void Skribot::EnterConfigMode(){
      config_mode = true;
    }
    void Skribot::ExitConfigMode(){
      if(config_mode){
        config_mode = false;
      }
    }