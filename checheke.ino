

#include "Basic/ir.h"
#include "Basic/motor.h"
#include "Basic/defines.h"

#include "Basic/tracking.h"
#include "Basic/detectOnblock.h"


const int TRACKING = 0;
const int ON_BLOCK = 1;
const int TURN = 2;

int state = TRACKING;





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
      state = TURN;
    }
  }else if(state==TURN){
    MotorWriting(0,0);
    delay(5000);
    state = TRACKING;
  }
}







