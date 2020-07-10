#include "Skribot.h"

#ifdef ESP_H
 void Skribot::SendMessageLine(int info){
 	Serial.println(info);
 }
 
 void Skribot::SendMessageLine(char *info){
 	Serial.println(info);
 }

 void Skribot::SendMessage(int info){
 	Serial.print(info);
 }
 
 void Skribot::SendMessage(char *info){
 	Serial.print(info);
 }
#endif
void Skribot::IgnoreCONBRK(){
    #ifdef DEBUG_MODE
      Serial.println("Ignoring conbreak!");
    #endif
    ignore_connection_break = true;
  }

  void Skribot::CONBRK(){
    #ifdef DEBUG_MODE
      Serial.println("Respecting conbreak!");
    #endif
    ignore_connection_break = false;
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
    if(ignore_connection_break)return(true);
    
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
      if(stausLEDused)status->ReadBatteryState();
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
    ledMatrix.begin(2500);
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
    #ifdef ESP_H
    ESP.restart();
    #endif
  
  }

  void Skribot::BLE_Flush(){
      while(BLE_dataAvailable())BLE_read();
  }

  void Skribot::BLE_Flush_Line(){
      while(true){
        if(BLE_dataAvailable()){
          char tmp = BLE_read();
          Serial.print(tmp);
          if(tmp == '\n')break;
        }else{
          break;
        }
      }
    }