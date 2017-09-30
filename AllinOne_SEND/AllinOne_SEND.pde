
int serialinput;
int pin2 = 2;
int pin4 = 4;
int pin7 = 7;
int pin8 = 8;
int potSpeed=0;
int potPin1=1;
int potPin2=2;
int potPin3=3;
int potPin4=4;

int val1= -1, val2 = -1, val3 = -1, val4 = -1, 
val5 = -1, val6 = -1;

void setup ()
{
  Serial.begin(9600);
  Serial.println("Setup Successful");
  pinMode(pin2, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin7, INPUT);
  pinMode(pin8, INPUT);
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
         Serial.println("R");
         delay(50);
       }       
      if (digitalRead(4)==0)
       {
         Serial.println("F");
         delay(50);
       } 
       
      if (digitalRead(7)==0)
       {
         Serial.println("B");
         delay(50);
       }
    if (digitalRead(8)==0)
      {
        Serial.println("L");
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
    newInput = map(analogRead(potPin1),0,1023,0,9);
  if(newInput != val2)
  {
    val2 = newInput;
    Serial.println("b");
    delay(50);
    Serial.println(val2);
    delay(50);
  }

  newInput = map(analogRead(potPin2),0,1023,0,9);
  if(newInput != val3)
  {
    val3 = newInput;
   Serial.println("c");
    delay(50);
    Serial.println(val3);
    delay(50);
  }

  newInput = map(analogRead(potPin3),0,1023,0,9);
  if(newInput != val4)
  {
    val4 = newInput;
    Serial.println("d");
    delay(50);
    Serial.println(val4);
    delay(50);
  }

  newInput = map(analogRead(potPin4),0,1023,0,9);
  if(newInput != val5)
  {
    val5 = newInput;
    Serial.println("e");
    delay(50);
    Serial.println(val5);
    delay(50);
  }
    Serial.flush();
}//end readSerial
