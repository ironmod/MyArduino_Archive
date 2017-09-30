
int serialinput;
int pwm_left = 3;  
int pwm_right = 11;  
int dir_left = 12;  
int dir_right = 13; 
int fadevalue = 0;
int pin2 = 2;
int pin3 =3;
int pin4 =4;
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
       
       if (digitalRead(2)==0)
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
       
       if (digitalRead(3)==0)
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
       
       if (digitalRead(4)==0)
       {
         Serial.println("Full Speed");
         for (; fadevalue <=255; fadevalue+=5)
        { 
         analogWrite(pwm_left, fadevalue);
         analogWrite(pwm_right, fadevalue);
        }
        
       }
}//end readSerial
