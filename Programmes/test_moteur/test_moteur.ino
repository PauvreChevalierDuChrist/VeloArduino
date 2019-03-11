#include<Wire.h>

int ENA=3; //Connecté à Arduino pin 9(sortie PWM)
int IN1=4; //Connecté à Arduino pin 4
int IN2=5; //Connecté à Arduino pin 5
//-- MOTEUR B --
int ENB=11; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=7; //Connecté à Arduino pin 6
int IN4=6; //Connecté à Arduino pin 7


const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
const int numReadings = 10;

int readings[numReadings];   

char Data;

void setup() {

Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  

pinMode(ENA,OUTPUT); // Configurer
pinMode(ENB,OUTPUT); // les broches
pinMode(IN1,OUTPUT); // comme sortie
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);

Serial.begin(115200);

digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);

}
void loop(){ 
  analogWrite(ENB,255);
  analogWrite(ENA, 255);

}
