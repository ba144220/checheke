#include "defines.h"



bool detectOnblock(){
    int ir[5];

  ir[0] = analogRead(IR1);
  ir[1] = analogRead(IR2);
  ir[2] = analogRead(IR3);
  ir[3] = analogRead(IR4);
  ir[4] = analogRead(IR5);  

  int numDetected = 0;
  
  if(ir[0] > threshold){
     numDetected++; 
  }
  if(ir[4] > threshold){
     numDetected++; 
  }
  if(ir[1] > threshold){
     numDetected++; 
  }
  if(ir[3] > threshold){
     numDetected++; 
  }

    if(ir[2] > threshold){
    numDetected++;    
  }
  if(numDetected<2){
      // change state
    return true;
  }

  return false;

}