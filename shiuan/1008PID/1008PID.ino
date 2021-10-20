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

int lastDetected = 2;

const int threshold = 300;

const int VL = 180;
const int VR = 180;   
static double integral = 0;
static bool lastdir, nodedir;
static double veloR = 0, veloL = 0;


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


  bool meetNode = tracking();
  if(meetNode) delay(5000);
  delay(10);
  meetNode = tracking();
  if(meetNode) delay(5000);
  delay(10);
  MotorWriting(0,0);
  delay(20);
  
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



bool tracking(){
    double coe = 0.4;
    double error = 0;
    double maxvel = 20;
    if(integral > maxvel){
      integral = maxvel;
    }
    else if(integral < -maxvel){
      integral = -maxvel;
    }

    int ir[5];

    ir[0] = analogRead(IR1);
    ir[1] = analogRead(IR2);
    ir[2] = analogRead(IR3);
    ir[3] = analogRead(IR4);
    ir[4] = analogRead(IR5);  

    if((ir[0]>threshold || ir[4]>threshold) && ir[1] > threshold && ir[2] > threshold && ir[3] > threshold){
        return 1;
    }

    if(ir[0] > threshold){
        error = 1;
        lastdir = 0;
    }
    else if(ir[1] > threshold){
        error = 0.5;
    }
    else if(ir[2] > threshold){
        error = 0;
    }
    else if(ir[3] > threshold){
        error = -0.5;
    }
    else if(ir[4] > threshold){
        error = -1;
        lastdir = 1;
    }
    else {
        error = -2;
    }


    if(error == -2){
      if(lastdir == 0){
        veloR = -75;
        veloL = -90;
      }
      else if(lastdir == 1)
        veloR = -90;
        veloL = -75;
    }
    else{
        integral += error;
        veloR = 160 + 27*error - coe*integral;
        veloL = 160 - 27*error + coe*integral;
    }

    MotorWriting(veloL, veloR);
    #ifdef DEBUG
      Serial.print("R : ");
      Serial.print(veloR);
      Serial.print(" L : ");
      Serial.print(veloL);
      Serial.print('\n');
    #endif
      return 0;
}
