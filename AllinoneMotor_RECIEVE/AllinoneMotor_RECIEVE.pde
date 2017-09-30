 #include <Servo.h>
int Servo2Pin = 9;
int Servo3Pin = 5;
int Servo4Pin = 6;
int Servo5Pin = 10;

Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
int potSpeed=0;
int serialinput;
int pwm_left = 3;  
int pwm_right = 11;  
int dir_left = 12;  
int dir_right = 13; 
int speed_select;

int val1= -1, val2 = -1, val3 = -1, val4 = -1, 
val5 = -1, val6 = -1;

void setup()
{
  Serial.begin(9600);
  pinMode(pwm_left, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir_left, OUTPUT);
  pinMode(dir_right, OUTPUT);
  analogWrite(pwm_left, 0);          
  analogWrite(pwm_right, 0);
  Servo2.attach(Servo2Pin);
  Servo3.attach(Servo3Pin);
  Servo4.attach(Servo4Pin);
  Servo5.attach(Servo5Pin);
}

void loop()
{
  while(Serial.available() == 0);

  char flag = Serial.read();
  int pos1, pos2, pos3, pos4, pos5, pos6;
  
  if( flag > -1)
  {
   Serial.println(flag);
    if(flag == 'F')
    {
   // Serial.println("Reverse");
      digitalWrite(dir_left, HIGH);  
      digitalWrite(dir_right, HIGH);  
     }
    if(flag == 'B')
    {
     //    Serial.println("Forward");
         digitalWrite(dir_left, LOW);  
         digitalWrite(dir_right, LOW);  
    } 
   if(flag == 'L')
       {
       //  Serial.println("Move Left");
         digitalWrite(dir_left, LOW);  
         digitalWrite(dir_right, HIGH);  
       }
  
    if(flag == 'R')
       {
         //Serial.println("Move Right);
         digitalWrite(dir_left, HIGH);  
         digitalWrite(dir_right, LOW);  
       }
    //speed adjust
    if(flag == 'S')
    {
       int value = Serial.read() - '0';
       while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        speed_select = map(value, 0, 9, 0, 255);
       analogWrite(pwm_left, speed_select);
       analogWrite(pwm_right, speed_select);
    }
    //servos
   if(flag == 'b')
    {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos2 = map(value, 0, 9, 0, 180);
        Servo2.write(pos2);
    }
   if(flag == 'c')
    {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos3 = map(value, 0, 9, 0, 180);
        Servo3.write(pos3);
    }
  
   if(flag == 'd')
    {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos4 = map(value, 0, 9, 0, 180);
        Servo4.write(pos4);
    }
  
  if(flag == 'e')
    {
        int value = Serial.read() - '0';
        while(value < -1)
          value = Serial.read() - '0';
        Serial.println(value);
        pos5 = map(value, 0, 9, 0, 180);
        Servo5.write(pos5);
    }
   }
  
  Serial.flush();
}
