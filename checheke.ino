

#include "Basic/ir.h"
#include "Basic/motor.h"
#include "Basic/defines.h"
#include "Basic/constants.h"



int lastDetected = 2;

const int threshold = 700;


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
    tracking();
    delay(15);
    tracking();
    delay(15);
    tracking();
    delay(15);
    tracking();
    delay(15);
    MotorWriting(0,0);
    delay(20);    
  }else if(state==ON_BLOCK){
    MotorWriting(150,150);
    delay(20);
    MotorWriting(0,0);
    delay(15);
    detectOnblock();
  }else if(state==TURN){
    MotorWriting(0,0);
    delay(5000);
    state = TRACKING;
  }
 

}

void detectOnblock(){
    int ir[5];

  ir[0] = analogRead(IR1);
  ir[1] = analogRead(IR2);
  ir[2] = analogRead(IR3);
  ir[3] = analogRead(IR4);
  ir[4] = analogRead(IR5);  

  int numDetected = 0;
  
  if(ir[0] > threshold){
    lastDetected = 0;
     numDetected++; 
  }
  if(ir[4] > threshold){
    lastDetected = 4;
     numDetected++; 
  }
  if(ir[1] > threshold){
    lastDetected = 1;
     numDetected++; 
  }
  if(ir[3] > threshold){
    lastDetected = 3;
     numDetected++; 
  }

    if(ir[2] > threshold){
    lastDetected = 2;
    numDetected++;    
  }
  if(numDetected<2){
    state = TURN;
  }

}




void tracking(){
  int ir[5];

  ir[0] = analogRead(IR1);
  ir[1] = analogRead(IR2);
  ir[2] = analogRead(IR3);
  ir[3] = analogRead(IR4);
  ir[4] = analogRead(IR5);  

  int numDetected = 0;
  
  if(ir[0] > threshold){
    lastDetected = 0;
     numDetected++; 
  }
  if(ir[4] > threshold){
    lastDetected = 4;
     numDetected++; 
  }
  if(ir[1] > threshold){
    lastDetected = 1;
     numDetected++; 
  }
  if(ir[3] > threshold){
    lastDetected = 3;
     numDetected++; 
  }

    if(ir[2] > threshold){
    lastDetected = 2;
    numDetected++;    
  }
  if(numDetected>3){
    state = ON_BLOCK;
  }

  if(lastDetected==0){
    MotorWriting(-100 , 100 );
  }else if(lastDetected==1){
    MotorWriting(100 , 160 );
  }else if(lastDetected==2){
    MotorWriting( 180 , 180  );
  }else if(lastDetected==3){
    MotorWriting( 160 , 100 );
  }else if(lastDetected==4){
   MotorWriting( 100 , -100 );
  }
  
}
