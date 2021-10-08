#include "defines.h"

void readIR(){
  int ir[5];

  ir[0] = analogRead(IR1);
  ir[1] = analogRead(IR2);
  ir[2] = analogRead(IR3);
  ir[3] = analogRead(IR4);
  ir[4] = analogRead(IR5);

  Serial.print(" IR1:");
  Serial.print(ir[0]);  
  Serial.print(" IR2:");
  Serial.print(ir[1]); 
  Serial.print(" IR3:");
  Serial.print(ir[2]);  
  Serial.print(" IR4:");
  Serial.print(ir[3]);  
  Serial.print(" IR5:");
  Serial.print(ir[4]);  

  Serial.println();


}
