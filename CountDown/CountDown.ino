int o1=3;
int o2=4;
int o3=5;
int o4=6;
int o5=7;
int o6=8;
int o7=9;
int o8=10;

void setup (){
  pinMode(o1, OUTPUT);
  pinMode(o2, OUTPUT);
  pinMode(o3, OUTPUT);
  pinMode(o4, OUTPUT);
  pinMode(o5, OUTPUT);
  pinMode(o6, OUTPUT);
  pinMode(o7, OUTPUT);
  pinMode(o8, OUTPUT);
  Serial.println("Count down begins.");
}
  

void loop (){
  digitalWrite(o1, HIGH);
  digitalWrite(o2, HIGH);
  digitalWrite(o3, HIGH);
 // digitalWrite(o4, HIGH);
  digitalWrite(o5, HIGH);
  digitalWrite(o6, HIGH);
  //digitalWrite(o7, HIGH);
  digitalWrite(o8, HIGH);
  delay(1000);
  off();
  digitalWrite(o2, HIGH);
  digitalWrite(o3, HIGH);
  delay(1000);
  off();
  digitalWrite(o1, HIGH);
  digitalWrite(o2, HIGH);
  digitalWrite(o5, HIGH);
  digitalWrite(o6, HIGH);
  digitalWrite(o7, HIGH);
  delay(1000);
  off();
  digitalWrite(o1, HIGH);
  digitalWrite(o2, HIGH);
  digitalWrite(o5, HIGH);
  digitalWrite(o3, HIGH);
  digitalWrite(o7, HIGH);
  delay(1000);
  off();
  digitalWrite(o2, HIGH);
  digitalWrite(o7, HIGH);
  digitalWrite(o3, HIGH);
  digitalWrite(o8, HIGH);
  delay(1000);
  off();
  digitalWrite(o1, HIGH);
  digitalWrite(o7, HIGH);
  digitalWrite(o8, HIGH);
  digitalWrite(o3, HIGH);
  digitalWrite(o5, HIGH);
  delay(1000);
  off();
  digitalWrite(o1, HIGH);
  digitalWrite(o7, HIGH);
  digitalWrite(o8, HIGH);
  digitalWrite(o3, HIGH);
  digitalWrite(o5, HIGH);
  digitalWrite(o6, HIGH);
  delay(1000);
  off();
  digitalWrite(o1, HIGH);
  digitalWrite(o2, HIGH);
  digitalWrite(o3, HIGH);
  delay(1000);
  off();
  digitalWrite(o1, HIGH);
  digitalWrite(o2, HIGH);
  digitalWrite(o3, HIGH);
  //digitalWrite(o4, HIGH);
  digitalWrite(o5, HIGH);
  digitalWrite(o6, HIGH);
  digitalWrite(o7, HIGH);
  digitalWrite(o8, HIGH);
  delay(1000);
  off();
  
}
  
  
void off (){
  digitalWrite(o1, LOW);
  digitalWrite(o2, LOW);
  digitalWrite(o3, LOW);
  digitalWrite(o4, LOW);
  digitalWrite(o5, LOW);
  digitalWrite(o6, LOW);
  digitalWrite(o7, LOW);
  digitalWrite(o8, LOW);  
  delay(1000);
}
