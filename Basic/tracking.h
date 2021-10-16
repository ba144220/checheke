#include "defines.h"


void tracking(int irRes){
    static int lastDetected = 2 ;

    if(irRes>=0){
        lastDetected = irRes;
    }
    

  if(lastDetected==0){
    MotorWriting( 0 , 150 );
  }else if(lastDetected==1){
    MotorWriting(130 , 160 );
  }else if(lastDetected==2){
    MotorWriting( 150 , 150  );
  }else if(lastDetected==3){
    MotorWriting( 160 , 130 );
  }else if(lastDetected==4){
   MotorWriting( 150 , 0 );
  }
  
}