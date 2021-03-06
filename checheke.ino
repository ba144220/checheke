

#include "Basic/ir.h"
#include "Basic/motor.h"
#include "Basic/defines.h"

#include "Basic/tracking.h"
#include "Basic/turn.h"
#include "Basic/detectOnblock.h"


const int TRACKING = 0;
const int ON_BLOCK = 1;
const int TURN = 2;
const int END = 3;



int state = TRACKING;

//const int commands[15] = {FORWARD,UTURN, RIGHT,FORWARD, RIGHT,RIGHT,UTURN,LEFT,RIGHT,RIGHT,UTURN,FORWARD,LEFT,FORWARD,STOP};
const int commands[8] = {FORWARD,FORWARD,FORWARD,LEFT,RIGHT,LEFT,LEFT,STOP};

int command_pos = 0;



void setup() {
  Serial.begin(9600);
  
    pinMode(ENB, OUTPUT); 
    pinMode(IN4, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    pinMode(IR3, INPUT);
    pinMode(IR4, INPUT);
    pinMode(IR5, INPUT);

    
}

void loop() {
 
  if(state==TRACKING){
    for(int i=0; i<5; i++){
      int irRes = readIR();
      if(irRes%100 > 3){
        state = ON_BLOCK;
      }
      tracking(irRes/100);
      delay(5);
    }
    MotorWriting(0,0);
    delay(15);    

  }else if(state==ON_BLOCK){

    MotorWriting(150,150);
    delay(20);
    MotorWriting(0,0);
    delay(15);
    int irRes = readIR();
    if(irRes%100<3){
      // for(int i=0; i<3; i++){
      //   MotorWriting(150,150);
      //   delay(20);
      //   MotorWriting(0,0);
      //   delay(15);
      // }
      MotorWriting(0,0);
      delay(500);
      state = TURN;
    }
  }else if(state==TURN){
    if(commands[command_pos]==FORWARD){
      MotorWriting(0,0);
      delay(500);
      int irRes = readIR();
      if(irRes%100==0){
        for(int i=0; i<20; i+=2){
          for(int j=0; j<i; j++){
            int irRes = readIR();
            if(irRes%100>0){
              goto changeState;
            }
            MotorWriting( -150, 180 );
            delay(30);
            MotorWriting(0,0);
            delay(60);
          }
          for(int j=0; j<i+1; j++){
            int irRes = readIR();
            if(irRes%100>0){
              goto changeState;
            }
            MotorWriting( 180, -150 );
            delay(30);
            MotorWriting(0,0);
            delay(60);            
          }
        }  
      }

      changeState:
      state = TRACKING;
      command_pos++;
    }else if(commands[command_pos]==STOP){
        MotorWriting( 0, 0 );
        delay(10000);
        state = END;
    }else{

    
    for(int i=0; i<8;i++){

      if(commands[command_pos]==LEFT){
        MotorWriting( 0, 255 );
      }else if(commands[command_pos]==RIGHT){
        MotorWriting( 255, 0 );
      }else if(commands[command_pos]==UTURN){
        MotorWriting( 0, 255 );
      }
      
      delay(40);
      MotorWriting(0,0);
      delay(40);

    }
    MotorWriting(0,0);
    delay(800);
    while(true){
      int irRes = readIR();
       if(commands[command_pos]==LEFT){
        MotorWriting( -150, 180 );
      }else if(commands[command_pos]==RIGHT){
        MotorWriting( 180, -150 );
      }else if(commands[command_pos]==UTURN){
        MotorWriting( -150, 180 );
      }
      delay(30);
      MotorWriting(0,0);
      delay(60);

      if(irRes/100>=1 && irRes/100<=3){
        MotorWriting(0,0);
        delay(800);
        break;
      }
    }
    
    state = TRACKING;
    command_pos++;
    }
  }else if(state==END){
    MotorWriting(0,0);
  }
}







