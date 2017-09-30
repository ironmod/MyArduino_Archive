#include <Servo.h>

int serialinput;
int pwm_left = 3;   //ENA
int pwm_right = 5;  //ENB
int dir1_left = 8;  //IN1
int dir2_left = 9;   //IN2
int dir1_right = 12; //IN3
int dir2_right = 13; //IN4
int pan = 10;
int tilt = 11;
int echo = 6;
int trig = 2;

long microseconds=0;
int speed_select;
long range =0;
void setup()
{
  Serial.begin(9600);
  Serial.println("Motor Control Receiver");
  pinMode(pwm_left, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_right, OUTPUT);
  pinMode(dir1_left, OUTPUT);
  pinMode(dir2_left, OUTPUT);
  pinMode(dir1_right, OUTPUT);
  pinMode(dir2_right, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  
  analogWrite(pwm_left, 0);          
  analogWrite(pwm_right, 0);
  analogWrite(pan, 125);
  analogWrite(tilt, 125);
  
}

void loop()
{
  motorControl();
  
  pinMode(trig, OUTPUT);// attach pin 3 to Trig
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
   
  pinMode (echo, INPUT);//attach pin 4 to Echo
  microseconds = pulseIn(echo, HIGH);
  range = microseconds / 74 / 2;
  Serial.print("Range is : ");
  Serial.println(range);
  //delay(10);
    
}//end void loop


