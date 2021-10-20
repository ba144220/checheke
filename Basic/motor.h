
#include "defines.h"


void MotorWriting(double vL, double vR){

    if(vR > 255){
        vR = 255;
    }else if(vR < -255){
        vR = -255;
    }

    if(vL > 255){
        vL = 255;
    }else if(vL < -255){
        vL = -255;
    }

    if(vR >= 0){
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else if(vR < 0){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        vR = -vR;
    }
    if(vL >= 0){
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    else if(vL < 0){
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        vL = -vL;
    }
    analogWrite(ENA, vR);
    analogWrite(ENB, vL);
}
