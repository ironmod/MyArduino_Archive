
int serialinput;
int pin2 = 2;
int pin4 = 4;
int pin7 = 7;
int pin8 = 8;
int potSpeed=0;

int val1= -1, val2 = -1, val3 = -1, val4 = -1, 
val5 = -1, val6 = -1;

void setup ()
{
  Serial.begin(9600);
  Serial.println("Setup Successful");
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin7, INPUT_PULLUP);
  pinMode(pin8, INPUT_PULLUP);
}

void loop()
{
  if(digitalRead(pin2) || digitalRead(pin3) || digitalRead(pin7
  readSerial();
  delay (15);

}//end void loop

void readSerial()
{
       
      if (digitalRead(2)==0) 
       {
         Serial.println("R");
         delay(50);
       }       
      else if (digitalRead(4)==0)
       {
         Serial.println("F");
         delay(50);
       } 
       
      else if (digitalRead(7)==0)
       {
         Serial.println("B");
         delay(50);
       }
      else if (digitalRead(8)==0)
      {
        Serial.println("L");
      }
      
      else 
      {
        Serial.println("P");
      }
      
      
  int newInput = map(analogRead(potSpeed),0,1023,0,9);
    if(newInput != val1)
    {
      val1 = newInput;
      Serial.println("S");
      delay(50);
      Serial.println(val1);
      delay(50);
    }
    
}//end readSerial
