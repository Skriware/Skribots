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



