#include "Skribot.h"

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
    ignore_connection_break = false;
    program_Override_Reported = false;
    smartRotor = NULL;
    Board_type = BOARD_VERSION;
    if(predef != " ")Configure_Connections(predef);
    #ifdef ESP_H
    Serial.begin(115200);
    #endif
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


  void Skribot::Set_Line_Sensor_Logic_Border(String id, int line, int noline){
    if(!EEPROM.begin(64)){
          #ifdef DEBUG_MODE
          Serial.println("EEPROM init fail, aborting calibration");
          #endif
          return;
       }
                        int lb = noline +abs(line-noline)/2;
                        if(id == "L1")Write_EEPROM_INT(EEPROM_L1_BORDER_ADDR,lb);
                        if(id == "L2")Write_EEPROM_INT(EEPROM_L2_BORDER_ADDR,lb);
                        if(id == "L3")Write_EEPROM_INT(EEPROM_L3_BORDER_ADDR,lb);
                        #ifdef ESP_H 
                        EEPROM.commit(); 
                        #endif
                        delay(100);
                        if(!user_config){
                          EEPROM.write(EEPROM_SETTINGS_OVERRIDED_ADDR,1);
                          user_config = true;
                          #ifdef ESP_H 
                          EEPROM.commit(); 
                          #endif
                    
                        }
  Serial.print(id);
  Serial.println(" calibrated!");
}