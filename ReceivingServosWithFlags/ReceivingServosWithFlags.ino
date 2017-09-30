#include <Servo.h>

//int Servo1Pin = 10;
int Servo2Pin = 9;
int Servo3Pin = 5;
int Servo4Pin = 6;
int Servo5Pin = 10;
//int Servo6Pin = 5;

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
//Servo Servo6;

void setup()
{
  Serial.begin(9600);
  //Servo1.attach(Servo1Pin);
  Servo2.attach(Servo2Pin);
  Servo3.attach(Servo3Pin);
  Servo4.attach(Servo4Pin);
  Servo5.attach(Servo5Pin);
  //Servo6.attach(Servo6Pin);
}

void loop()
{
  while(Serial.available() == 0);

  char flag = Serial.read();
  int pos1, pos2, pos3, pos4, pos5, pos6;
  
  if( flag > -1)
  {
    Serial.println(flag);
    /*
  if(flag == 'a')
  {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        
        Serial.println(value);
        pos1 = map(value, 0, 9, 0, 180);
        Servo1.write(pos1);
  }
  */
  if(flag == 'b')
  {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos2 = map(value, 0, 9, 0, 180);
        Servo2.write(pos2);
  }
  
    if(flag == 'c')
  {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos3 = map(value, 0, 9, 0, 180);
        Servo3.write(pos3);
  }
  
    if(flag == 'd')
  {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos4 = map(value, 0, 9, 0, 180);
        Servo4.write(pos4);
  }
  
    if(flag == 'e')
  {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos5 = map(value, 0, 9, 0, 180);
        Servo5.write(pos5);
  }
  /*
    if(flag == 'f')
  {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos6 = map(value, 0, 9, 0, 180);
        Servo4.write(pos6);
  }
  */
  }
  
  Serial.flush();
}
