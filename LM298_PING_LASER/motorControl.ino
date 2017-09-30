void motorControl()
{
    char flag;
  if(Serial.available())
  {
    flag = Serial.read();
    int pos1, pos2, pos3, pos4, pos5, pos6;
    Serial.println(flag);

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

} //end motorControl

