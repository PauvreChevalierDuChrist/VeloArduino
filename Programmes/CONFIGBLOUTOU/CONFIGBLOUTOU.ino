#include<SoftwareSerial.h>
#define TX 9
#define RX 12
SoftwareSerial BlueT(RX,TX);

void setup(){
Serial.begin(9600);
delay(500);
BlueT.begin(9600);
delay(500);
}


void loop(){
while (BlueT.available()) {
Serial.print(char(BlueT.read())); }
while (Serial.available()) {
BlueT.write(char(Serial.read())); }
}
