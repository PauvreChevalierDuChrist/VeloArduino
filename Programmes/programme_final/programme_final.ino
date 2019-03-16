#include <MPU6050.h>
#include<Wire.h>
#include <PID_v1.h>
#include<SoftwareSerial.h>

MPU6050 accelgyro;
#define RX 12
#define TX 9
char Data;
int vitesseB;
SoftwareSerial BlueT(RX,TX);
//--MOTEUR A -- ROUE INERTIE
int ENA=3; 
int IN1=4; 
int IN2=5; 
//-- MOTEUR B -- ROUE ARRIERE
int ENB=9; 
int IN3=6; 
int IN4=7; 

int value;
int value2 = 0;


int sensVal;           
float filterVal = 0.001;       
float smoothedVal;    

int i, j;  
const int MPU=0x68;  
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
const int numReadings = 10;

int readings[numReadings];      
int index = 0;                  
int total = 0;                  
int average = 0;                

int goal = 300;
double Input;
double Output;
double Setpoint = 0;
int Kp = 10;
int Ki = 0.1;
int Kd = 0.5;
PID balancePID(&Input,&Output,&Setpoint,Kp,Ki,Kd,DIRECT);  

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);
  balancePID.SetMode(AUTOMATIC);
  balancePID.SetOutputLimits(-255,255);
  Serial.begin(115200);   
  BlueT.begin(9600);      

  pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT); 

pinMode(IN1,OUTPUT); 
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);


//digitalWrite(IN3,LOW);
//digitalWrite(IN4,HIGH);
//digitalWrite(IN1,LOW);
//digitalWrite(IN2,HIGH);

accelgyro.setXAccelOffset(-630);
  accelgyro.setYAccelOffset(-1125);
  accelgyro.setZAccelOffset(1207);
  accelgyro.setXGyroOffset(104);
  accelgyro.setYGyroOffset(28);
  accelgyro.setZGyroOffset(22);
  
}
void loop(){
  Input = smooth(readGyro(),filterVal,smoothedVal);
  
  balancePID.Compute();
  //Serial.println(Input);
  if(Output < 0){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    Serial.println((Output));
    value = abs((Output));
      motorSpeed(value);
  }
  if(Output > 0){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    
    value = (abs((Output)));
    Serial.println(value);
      motorSpeed(value);
  }
Data=BlueT.read();
if (Data=='B'){
    int vitessetempB=BlueT.parseInt();
    Serial.println(BlueT.parseInt());
    vitesseB=abs(BlueT.parseInt());
    Serial.println(vitesseB);
  analogWrite(ENB,vitesseB);

  if(vitessetempB<0){
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    }
  else {
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    }
    }

}

int motorSpeed(int newValue){
  analogWrite(ENA, newValue);

}

int averageValue(int GyX){
    total= total - readings[index];
    readings[index] = GyX;
    total= total + readings[index];     
    index = index + 1;                    
    if (index >= numReadings){              
      index = 0;                          
    }
    average = total / numReadings;  
   return average;   
}





int readGyro(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  
  
  AcX=Wire.read()<<8|Wire.read();      
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  Tmp=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();
  
  //Serial.println(AcY);
  if(AcY < 0){
    return AcY;
  }
  if(AcY > 0){
    return AcY;
  }
}

int smooth(int data, float filterVal, float smoothedVal){


  if (filterVal > 1){
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}
