#include "Skribot.h"

#define EEPROM_EMPTY_ESP32 255
#define EEPROM_EMPTY_ARDUINO 0

bool Skribot::EEPROM_EMPTY(int val){
    return(val == EEPROM_EMPTY_ESP32 || val == EEPROM_EMPTY_ARDUINO);
  }

bool Skribot::Check_Board_Version(){
      #ifdef DEBUG_MODE
          Serial.println("Checking EEPROM...");
      #endif
       #ifdef ESP_H
       if(!EEPROM.begin(64)){
          #ifdef DEBUG_MODE
          Serial.println("EEPROM init fail, aborting EEPROM check.");
          #endif
          return(false);
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
        return(false);
      }else{
        #ifdef DEBUG_MODE
        Serial.print("BOARD VERSION:");
        Serial.println(Board_type);
        #endif
        
      #ifdef FORCE_BOARD_VERSION
        #ifdef FORCE_BOARD_VERSION_1
          Board_type = 1;
        #endif
        #ifdef FORCE_BOARD_VERSION_2
          Board_type = 2;
        #endif
        EEPROM.write(EEPROM_BOARD_VERSION_ADDR,Board_type);
        #ifdef ESP_H 
          EEPROM.commit(); 
        #endif
      #endif
         
          
        return(true);
      }
  }

  bool Skribot::ConfigureBoardEEPROM(){
       if(!EEPROM.begin(64)){
          #ifdef DEBUG_MODE
          Serial.println("EEPROM init fail, aborting EEPROM check.");
          #endif
          return(false);
       }
       delay(10);                                              //EEPROM delay in order to avoid EEPROM ERRORS
       byte userChange = EEPROM.read(EEPROM_SETTINGS_OVERRIDED_ADDR);
       delay(10);
       if(EEPROM_EMPTY(userChange)){
         #ifdef DEBUG_MODE
          Serial.println("No user Settings in EEPROM Configuration");
        #endif
          user_config = false;
        return(false);                                                                         //No user change done aborting the process;
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
       return(true);
   
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