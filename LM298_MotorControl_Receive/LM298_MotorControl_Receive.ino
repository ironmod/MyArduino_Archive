#include <Servo.h>

int serialinput;
int pwm_left = 3;   //ENA
int pwm_right = 5;  //ENB
int dir1_left = 8;  //IN1
int dir2_left = 9;   //IN2
int dir1_right = 12; //IN3
int dir2_right = 13; //IN4
int speed_select;

void setup()
{
  Serial.begin(9600);
  Serial.println("Motor Control Receiver");
  pinMode(pwm_left, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir1_left, OUTPUT);
  pinMode(dir2_left, OUTPUT);
  pinMode(dir1_right, OUTPUT);
  pinMode(dir2_right, OUTPUT);
  analogWrite(pwm_left, 0);          
  analogWrite(pwm_right, 0);
}

void loop()
{
  char flag;
  if(Serial.available())
  {
    flag = Serial.read();
    int pos1, pos2, pos3, pos4, pos5, pos6;
    Serial.println(flag);
    
   // if( flag > -1 )
    //{
      Serial.println(flag);
      if(flag == 'B')
      {
        //Serial.println("Reverse");
        digitalWrite(dir1_left, HIGH);
        digitalWrite(dir2_left, LOW);  
        digitalWrite(dir1_right, HIGH);
        digitalWrite(dir2_right, LOW);  
      }
      
    else if(flag == 'F')
      {
        //Serial.println("Forward");
        digitalWrite(dir1_left, LOW);
        digitalWrite(dir2_left, HIGH);  
        digitalWrite(dir1_right, LOW);
        digitalWrite(dir2_right, HIGH);  
      } 
      
    else if(flag == 'L')
        {
         //Serial.println("Move Left");
         digitalWrite(dir1_left, LOW);
         digitalWrite(dir2_left, HIGH);  
         digitalWrite(dir1_right, HIGH);
         digitalWrite(dir2_right, LOW);  
        }
      
    else if(flag == 'R')
       {
         //Serial.println("Move Right");
         digitalWrite(dir1_left, HIGH);
         digitalWrite(dir2_left, LOW);  
         digitalWrite(dir1_right, LOW);
         digitalWrite(dir2_right, HIGH);  
       }
    else if (flag=='P')
    {
      digitalWrite(dir1_left, LOW);
      digitalWrite(dir2_left, LOW);  
      digitalWrite(dir1_right, LOW);
      digitalWrite(dir2_right, LOW);  
    }

  
   //speed adjust    
   //flag = Serial.read();
    if(flag == 'S')
    {
      int value = Serial.read() - '0';
      while(value < -1)
      //{
        value = Serial.read() - '0';
        //Serial.println(value);
        speed_select = map(value, 0, 9, 0, 255);
        analogWrite(pwm_left, speed_select);
        analogWrite(pwm_right, speed_select);
      //}//end while
    }//end Speed adjust
}//end while
    
}//end void loop
