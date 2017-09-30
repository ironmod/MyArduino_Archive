void MotorControl()
{
int pwm_left = 10;   //ENA
int pwm_right = 11;  //ENB
int dir1_left = 7;  //IN1
int dir2_left = 9;   //IN2
int dir1_right = 12; //IN3
int dir2_right = 13; //IN4

char flag;

  if (reverse)
    {
      digitalWrite(dir1_left, HIGH);
      digitalWrite(dir2_left, LOW);  
      digitalWrite(dir1_right, HIGH);
      digitalWrite(dir2_right, LOW);  
    }
    
  else if(forward)
    {
      digitalWrite(dir1_left, LOW);
      digitalWrite(dir2_left, HIGH);  
      digitalWrite(dir1_right, LOW);
      digitalWrite(dir2_right, HIGH);  
    } 
    
  else if(left)
      {
       digitalWrite(dir1_left, LOW);
       digitalWrite(dir2_left, HIGH);  
       digitalWrite(dir1_right, HIGH);
       digitalWrite(dir2_right, LOW);  
      }
    
  else if(right)
     {
       digitalWrite(dir1_left, HIGH);
       digitalWrite(dir2_left, LOW);  
       digitalWrite(dir1_right, LOW);
       digitalWrite(dir2_right, HIGH);  
     }
     
  else //shut all motors off
    {
      digitalWrite(dir1_left, LOW);
      digitalWrite(dir2_left, LOW);  
      digitalWrite(dir1_right, LOW);
      digitalWrite(dir2_right, LOW);  
    }
  
  speedCtrl=analogRead(A1);
  speedCtrl = map(speedCtrl, 0, 1023, 0, 255);
  analogWrite(pwm_left, speedCtrl);
  analogWrite(pwm_right, speedCtrl);
  gUpdateValue(&speedCtrl);


} //end motorControl
