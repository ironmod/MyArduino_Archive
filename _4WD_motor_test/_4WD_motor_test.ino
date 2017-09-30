int IN1 = 2;
int IN2 = 4;
int IN3 = 6;
int IN4 = 7;
int IN5 = 8;
int IN6 = 9;
int IN7 = 12;
int IN8 = 13;
int ENA = 3;
int ENB = 5;
int ENAA = 10;
int ENBB = 11;
int i=0;

void setup()
{
  Serial.begin(38400);
  delay(500);
  Serial.write(254); // move cursor to beginning of first line
  Serial.write(128);

  Serial.write("                "); // clear display
  Serial.write("                ");
  
  delay(1000);
  Serial.write(254); // move cursor to beginning of first line
  Serial.write(128);
  Serial.write("Hello, world!");

  for (i=2; i<14; i++)
  {
    pinMode(i, OUTPUT);
  }
  
  delay(20);

  //Forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  analogWrite(ENAA, 255);
  analogWrite(ENBB, 255);  
 delay(2000);
}

void loop ()
{
  
//Forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);  
  Serial.write(254); // move cursor to beginning of first line
  Serial.write(128);
  Serial.write("                "); // clear display
  Serial.write("                ");
    
  for(i=125; i<255; i++)
  {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    analogWrite(ENAA, i);
    analogWrite(ENBB, i);
    Serial.write(254); // move cursor to beginning of first line
    Serial.write(128);
    Serial.write("Moving Forward...");
    Serial.write(254);
    Serial.write(192);
    Serial.write("Speed: ");
    Serial.print(i);
    delay(50);
  }
  
//Reverse
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);  
  Serial.write(254); // move cursor to beginning of first line
  Serial.write(128);
  Serial.write("                "); // clear display
  Serial.write("                ");
  
  for(i=125; i<255; i++)
  {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    analogWrite(ENAA, i);
    analogWrite(ENBB, i);
    Serial.write(254); // move cursor to beginning of first line
    Serial.write(128);
    Serial.write("Moving Reverse...");
    Serial.write(254);
    Serial.write(192);
    Serial.write("Speed: ");
    Serial.print(i);
    delay(50);
  }
  
//Left
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);  
  Serial.write(254); // move cursor to beginning of first line
  Serial.write(128);
  Serial.write("                "); // clear display
  Serial.write("                ");
  
  for(i=125; i<255; i++)
  {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    analogWrite(ENAA, i);
    analogWrite(ENBB, i);
    Serial.write(254); // move cursor to beginning of first line
    Serial.write(128);
    Serial.write("Moving Left...");
    Serial.write(254);
    Serial.write(192);
    Serial.write("Speed: ");
    Serial.print(i);
    delay(50);
  }
  
//Right
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);  
  Serial.write(254); // move cursor to beginning of first line
  Serial.write(128);
  Serial.write("                "); // clear display
  Serial.write("                ");
    
  for(i=125; i<255; i++)
  {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    analogWrite(ENAA, i);
    analogWrite(ENBB, i);
    Serial.write(254); // move cursor to beginning of first line
    Serial.write(128);
    Serial.write("Moving Right...");
    Serial.write(254);
    Serial.write(192);
    Serial.write("Speed: ");
    Serial.print(i);
    delay(50);
  }

}

