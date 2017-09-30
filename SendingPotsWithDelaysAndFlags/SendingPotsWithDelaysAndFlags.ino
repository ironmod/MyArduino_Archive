//int potPin1=0;
int potPin1=1;
int potPin2=2;
int potPin3=3;
int potPin4=4;
//int potPin6=5;

int val1 = -1, val2 = -1, val3 = -1, val4 = -1, 
val5 = -1, val6 = -1;

void setup()
{
Serial.begin(9600);
}

void loop()
{/*
int newInput = map(analogRead(potPin0),0,1023,0,9);
if(newInput != val1)
{
  val1 = newInput;
  Serial.println("a");
  delay(50);
  Serial.println(val1);
  delay(50);
}
*/
int newInput = map(analogRead(potPin1),0,1023,0,9);
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
/*
newInput = map(analogRead(potPin6),0,1023,0,9);
if(newInput != val6)
{
  val6 = newInput;
  Serial.println("f");
  delay(50);
  Serial.println(val6);
  delay(50);
}
*/

delay(50);

}
