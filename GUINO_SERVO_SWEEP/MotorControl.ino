void MotorControl()
{
int pwm_left = 3;   //ENA
int pwm_right = 5;  //ENB
int dir1_left = 8;  //IN1
int dir2_left = 9;   //IN2
int dir1_right = 12; //IN3
int dir2_right = 13; //IN4
char flag;

  if(Serial.available())
  {
    flag = Serial.read();
    int pos1, pos2, pos3, pos4, pos5, pos6;
    Serial.println(flag);

      Serial.println(flag);
      if(reverse)
      {
        //Serial.println("Reverse");
        digitalWrite(dir1_left, HIGH);
        digitalWrite(dir2_left, LOW);  
        digitalWrite(dir1_right, HIGH);
        digitalWrite(dir2_right, LOW);  
      }
      
    else if(forward)
      {
        //Serial.println("Forward");
        digitalWrite(dir1_left, LOW);
        digitalWrite(dir2_left, HIGH);  
        digitalWrite(dir1_right, LOW);
        digitalWrite(dir2_right, HIGH);  
      } 
      
    else if(left)
        {
         //Serial.println("Move Left");
         digitalWrite(dir1_left, LOW);
         digitalWrite(dir2_left, HIGH);  
         digitalWrite(dir1_right, HIGH);
         digitalWrite(dir2_right, LOW);  
        }
      
    else if(right)
       {
         //Serial.println("Move Right");
         digitalWrite(dir1_left, HIGH);
         digitalWrite(dir2_left, LOW);  
         digitalWrite(dir1_right, LOW);
         digitalWrite(dir2_right, HIGH);  
       }
    else 
    {
      digitalWrite(dir1_left, LOW);
      digitalWrite(dir2_left, LOW);  
      digitalWrite(dir1_right, LOW);
      digitalWrite(dir2_right, LOW);  
    }
    
    speedCtrl=analogRead(A1);
    gUpdateValue(&speedCtrl);
    //Serial.println(value);
    speedCtrl = map(speedCtrl, 0, 9, 0, 255);
    analogWrite(pwm_left, speedCtrl);
    analogWrite(pwm_right, speedCtrl);

  }
} //end motorControl
