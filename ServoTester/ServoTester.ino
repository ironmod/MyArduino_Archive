#include <Servo.h>

int Servo1Pin = 3;
int Servo2Pin = 5;
int Servo3Pin = 6;
int Servo4Pin = 9;
int Servo5Pin = 10;
//int Servo6Pin = 5;

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
//Servo Servo6;

int pot1=A0;
int pot2=A1;
int pot3=A2;
int pot4=A3;
int pot5=A4;

int pos1 = -1, pos2 =-1, pos3 = -1, pos4 = -1, 
pos5 = -1, pos6 = -1;

int temp1=0, temp2=0, temp3=0, temp4=0, temp5=0; 

void setup()
{
  Serial.begin(9600);
  Servo1.attach(Servo1Pin);
  Servo2.attach(Servo2Pin);
  Servo3.attach(Servo3Pin);
  Servo4.attach(Servo4Pin);
  Servo5.attach(Servo5Pin);
  //Servo6.attach(Servo6Pin);

}

void loop()
{
  pos1 = map(analogRead(pot1),0,1023,0,180);
  Servo1.write(pos1);
  if (temp1 != pos1)
    Serial.println(temp1);
  temp1=pos1;
    delay(10);
  
    pos2 = map(analogRead(pot2),0,1023,0,180);
  Servo2.write(pos2);
  delay(10);
  
    pos3 = map(analogRead(pot3),0,1023,0,180);
  Servo3.write(pos3);
  delay(10);
  
    pos4 = map(analogRead(pot4),0,1023,0,180);
  Servo4.write(pos4);
  delay(10);
  
    pos5 = map(analogRead(pot5),0,1023,0,180);
  Servo5.write(pos5);
  delay(10);
}
