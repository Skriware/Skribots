#include "Skribot.h"

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

  int Skribot::ReadLineSensorData(int id){
     for(int zz = 0; zz < NLineSensors ; zz++){
                    if(LineSensors[zz]->GetID() == id){
                      return(LineSensors[zz]->ReadSensorScaled());
                      break;
                    }
      }
      return(0);
  }

    int Skribot::ReadLineSensorData(String name){ 
    for(int zz = 0; zz < NLineSensors ; zz++){
                    if(LineSensors[zz]->GetName() == name){
                      return(LineSensors[zz]->ReadSensorScaled());
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

  void Skribot::Move(char Dir,int ms){
      if (NLeftDCRotors  > 0 && NRightDCRotors  >0){
         switch(Dir){
        case 'B':
                  for(int zz = 0; zz < NRightDCRotors ; zz++){
                    RightDCRotors[zz]->SetDirection(0);
                    RightDCRotors[zz]->SetSpeed(DCSpeed);
                    RightDCRotors[zz]->Move();
                  }

                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(0);
                    LeftDCRotors[kk]->SetSpeed(DCSpeed);
                    LeftDCRotors[kk]->Move();
                  }
        break;
        
        case 'F':
                  
                  for(int zz = 0; zz < NRightDCRotors ; zz++){
                    RightDCRotors[zz]->SetDirection(1);
                    RightDCRotors[zz]->SetSpeed(DCSpeed);
                    RightDCRotors[zz]->Move();
                  }

                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->SetSpeed(DCSpeed);
                    LeftDCRotors[kk]->Move();
                  }
        break;

        case 'R':
                  for(int zz = 0; zz < NLeftDCRotors ; zz++){
                    LeftDCRotors[zz]->SetDirection(1);
                    LeftDCRotors[zz]->SetSpeed(DCSpeed);
                    LeftDCRotors[zz]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(0);
                    RightDCRotors[kk]->SetSpeed(DCSpeed);
                    RightDCRotors[kk]->Move();
                  }
         break;

         case 'L':
                  for(int zz = 0; zz < NLeftDCRotors ; zz++){
                    LeftDCRotors[zz]->SetDirection(0);
                    LeftDCRotors[zz]->SetSpeed(DCSpeed);
                    LeftDCRotors[zz]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->SetSpeed(DCSpeed);
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
                    LeftDCRotors[kk]->SetSpeed(0.25*DCSpeed);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->SetSpeed(DCSpeed);
                    RightDCRotors[kk]->Move();
                  }
         break;

         case 'Z' :
                    for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->SetSpeed(0.25*DCSpeed);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->SetSpeed(DCSpeed);
                    RightDCRotors[kk]->Move();
                  }
         break;

         case 'M' :
                   for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(1);
                    LeftDCRotors[kk]->SetSpeed(DCSpeed);
                    LeftDCRotors[kk]->Move();
                  }
          
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(1);
                    RightDCRotors[kk]->SetSpeed(0.25*DCSpeed);
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

  void Skribot::Set_Motor_Movment(byte motor_id, byte dir, byte speed,int time){

          switch(motor_id){
           
            case LEFT:
                  for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetDirection(dir);
                    LeftDCRotors[kk]->SetSpeed(speed);
                    LeftDCRotors[kk]->Move();
                  }
            break;
            
            case RIGHT:
                  for(int kk = 0; kk < NRightDCRotors ; kk++){
                    RightDCRotors[kk]->SetDirection(dir);
                    RightDCRotors[kk]->SetSpeed(speed);
                    RightDCRotors[kk]->Move();
                  }
            break;
          }

          if(time > 0 ){
          wait_And_Check_BLE_Connection(time,10);
          for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->Stop();
                  }
          
           for(int k = 0; k < NRightDCRotors ; k++){
                    RightDCRotors[k]->Stop();
            }
            high_power_usage=false;
      }
  }

  void Skribot::Move_Motor_Forward(byte motor_id,byte speed,int time){
        Set_Motor_Movment(motor_id,1,speed,time);
  }


  void Skribot::Move_Motor_Back(byte motor_id,byte speed,int time){
        Set_Motor_Movment(motor_id,0,speed,time);
  }

  void Skribot::RawRotorMove(int left, int right){
     Serial.print("L:");
     Serial.print(left);
     Serial.print("R:");
     Serial.println(right);
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
                    RightDCRotors[kk]->SetSpeed(200*rightSpeed/250);
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
                    LeftDCRotors[yy]->SetSpeed(200*leftSpeed/250);
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
      if(s >100)s = 100;
      SetSpeed_Raw(s/2+90);
      DCSpeed = s/2+90;
    }
    void Skribot::SetSpeed_Raw(int s){ 
      for(int kk = 0; kk < NLeftDCRotors ; kk++){
                    LeftDCRotors[kk]->SetSpeed(s);
                    
                  }
          
      for(int jj = 0; jj < NRightDCRotors ; jj++){
                    RightDCRotors[jj]->SetSpeed(s);
                    
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

    void Skribot::SetLEDColor(int color_id){
      switch(color_id){
            case 0: 
                TurnLEDOn(255,0,0);
            break;
            case 1 : 
                TurnLEDOn(0,0,255);
            break;
             case 2 : 
                TurnLEDOn(0,255,0);
            break;
             case 4 : 
                TurnLEDOn(255,0,255);
            break;
             case 5 : 
                TurnLEDOn(255,255,255);
            break;
            case 3: 
                TurnLEDOn(184, 255, 3);
            break;
            default:
            break;
          }
    }
