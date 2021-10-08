#define ENB 3
#define IN4 4
#define IN3 5
#define ENA 6 
#define IN1 7
#define IN2 8
#define IR1 A1
#define IR2 A2
#define IR3 A3
#define IR4 A4
#define IR5 A5

const int TRACKING = 0;
const int ON_BLOCK = 1;
const int TURN = 2;

int state = TRACKING;


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
