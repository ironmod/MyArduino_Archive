
int serialinput;
int pwm_left = 3;  
int pwm_right = 11;  
int dir_left = 12;  
int dir_right = 13; 
//int fadevalue = 0;
int pin2 = 2;
int pin3 =7;
int pin4 =4;
int pin5 = 8;
int potPin1=0;
int potPin2=1;
int potPin3=2;
int potPin4=3;
int potPin5=4;
int potPin6=5;

int val1= -1, val2 = -1, val3 = -1, val4 = -1, 
val5 = -1, val6 = -1;

void setup ()
{
  Serial.begin(9600);
  Serial.println("Setup Successful");
  
  pinMode(pwm_left, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir_left, OUTPUT);
  pinMode(dir_right, OUTPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
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
       
       if (digitalRead(2)==0) // if ((serialinput=='w') || (serialinput=='W'));
       {
         Serial.println("Reverse");
         digitalWrite(dir_left, HIGH);  
         digitalWrite(dir_right, HIGH);  
       }
       
       if (digitalRead(4)==0)
       {
         Serial.println("Forward");
         digitalWrite(dir_left, LOW);  
         digitalWrite(dir_right, LOW);  
       } 
       
       if (digitalRead(7)==0)
       {
         Serial.println("Move Left");
         digitalWrite(dir_left, LOW);  
         digitalWrite(dir_right, HIGH);  
       }
       
         int newInput = map(analogRead(potPin2),0,1023,0,255);
    if(newInput != val1)
    {
      val1 = newInput;
      Serial.println("a");
      delay(50);
      Serial.println(val1);
      delay(50);
    }
    
    analogWrite(pwm_left, val1);
    analogWrite(pwm_right, val1);
       
  /*   if (digitalRead(8)==0)
       {
         Serial.println("Move Right");
         digitalWrite(dir_left, HIGH);  
         digitalWrite(dir_right, LOW);  
       }
  
  /*
       while (digitalRead(2)==0)
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
       
       while (digitalRead(7)==0)
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
       
       while (digitalRead(4)==0)
       {
         Serial.println("Full Speed");
         for (; fadevalue <=255; fadevalue+=5)
        { 
         analogWrite(pwm_left, fadevalue);
         analogWrite(pwm_right, fadevalue);
        }
        
       }
*/
}//end readSerial
