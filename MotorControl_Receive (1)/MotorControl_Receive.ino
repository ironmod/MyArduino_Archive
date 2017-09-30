#include <Servo.h>

int serialinput;
int pwm_left = 3;  
int pwm_right = 11;  
int dir_left = 12;  
int dir_right = 13; 
int speed_select;

void setup()
{
  Serial.begin(9600);
  pinMode(pwm_left, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir_left, OUTPUT);
  pinMode(dir_right, OUTPUT);
  analogWrite(pwm_left, 0);          
  analogWrite(pwm_right, 0);
}

void loop()
{
  while(Serial.available() == 0);

  char flag = Serial.read();
  int pos1, pos2, pos3, pos4, pos5, pos6;
  
  if( flag != 0)
  {
    Serial.println(flag);
    if(flag == 'B')
    {
      //Serial.println("Reverse");
      digitalWrite(dir_left, HIGH);  
      digitalWrite(dir_right, HIGH);  
    }
    
  else if(flag == 'F')
    {
      //Serial.println("Forward");
      digitalWrite(dir_left, LOW);  
      digitalWrite(dir_right, LOW);  
    } 
    
  else if(flag == 'L')
      {
       //Serial.println("Move Left");
       digitalWrite(dir_left, LOW);  
       digitalWrite(dir_right, HIGH);  
      }
    
    else if(flag == 'R')
     {
       //Serial.println("Move Right");
       digitalWrite(dir_left, HIGH);  
       digitalWrite(dir_right, LOW);  
     }

    //speed adjust
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
}
  else 
  {
    analogWrite(pwm_left, 0);
    analogWrite(pwm_right, 0);
  }
   
  
  Serial.flush();
}
