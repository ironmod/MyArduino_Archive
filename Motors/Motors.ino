
int serialinput;
int pwm_left = 3;  
int pwm_right = 11;  
int dir_left = 12;  
int dir_right = 13; 
int fadevalue = 0;

void setup ()
{
  Serial.begin(9600);
  Serial.println("Setup Successful");
  
  pinMode(pwm_left, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir_left, OUTPUT);
  pinMode(dir_right, OUTPUT);
  
  analogWrite(pwm_left, 0);          
  analogWrite(pwm_right, 0);
}

void loop()
{
  readSerial();
  delay (15);

}//end void loop

void readSerial()
{
  if(Serial.available()) {
    while (Serial.available()){
      serialinput=Serial.read ();
      
       if (serialinput=='s') // if ((serialinput=='w') || (serialinput=='W'));
       {
         Serial.println("Reverse");
         digitalWrite(dir_left, HIGH);  
         digitalWrite(dir_right, HIGH);  
       }
       
        if (serialinput=='w')
       {
         Serial.println("Forward");
         digitalWrite(dir_left, LOW);  
         digitalWrite(dir_right, LOW);  
       } 
       
       if (serialinput=='a')
       {
         Serial.println("Move Left");
         digitalWrite(dir_left, LOW);  
         digitalWrite(dir_right, HIGH);  
       }
       
       if (serialinput=='d')
       {
         Serial.println("Move Right");
         digitalWrite(dir_left, HIGH);  
         digitalWrite(dir_right, LOW);  
       }
       
       if (serialinput=='0')
       {
         Serial.println("Stop");
         for(; fadevalue >=0; fadevalue-=5)
         {
         analogWrite(pwm_left, fadevalue);
         analogWrite(pwm_right, fadevalue);
         }
       }
       
       if (serialinput=='1')
       { 
         Serial.println("Slow Speed");
         if (fadevalue > 50)
         {
           for (; fadevalue >= 50; fadevalue -= 5)
           {
             analogWrite(pwm_left, fadevalue);
             analogWrite(pwm_right, fadevalue);
           }
         }
         if (fadevalue < 50)
         {
           for (; fadevalue <= 50; fadevalue += 5)
           {
             analogWrite(pwm_left, fadevalue);
             analogWrite(pwm_right, fadevalue);
           }
         }
       }
       
       if (serialinput=='2')
       {
         Serial.println("Medium Speed");
         if (fadevalue < 150)
         {
           for(; fadevalue <= 150; fadevalue += 5)
           {
             analogWrite(pwm_left, 150);
             analogWrite(pwm_right, 150);
           }
         }
         if (fadevalue > 150)
         {
           for(; fadevalue >= 150; fadevalue -= 5)
           {
             analogWrite(pwm_left, fadevalue);
             analogWrite(pwm_right, fadevalue);
           }
         }
       }
       
       if (serialinput=='3')
       {
         Serial.println("Full Speed");
         for (; fadevalue <=255; fadevalue+=5)
        { 
         analogWrite(pwm_left, fadevalue);
         analogWrite(pwm_right, fadevalue);
        }
        
       }
    }//end while 
  }//end serial if
}//end readSerial
