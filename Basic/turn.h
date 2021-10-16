#include "defines.h"


// void turn(bool left=true){
//     const int turnRate = 150;
    
//     if(left){

//         MotorWriting( -1*turnRate , 1.2*turnRate );
//     }else{
//          MotorWriting( 1.2*turnRate , -1 * turnRate );
//     }
 
// }

void turn(bool left=true){
    const int turnRate = 150;
    
    if(left){

        MotorWriting( 0, 1.5*turnRate );
    }else{
         MotorWriting( 1.5*turnRate , 0);
    }
 
}