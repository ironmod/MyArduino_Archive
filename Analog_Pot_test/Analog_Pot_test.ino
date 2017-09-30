void setup() {
  Serial.begin(9600);
  Serial.println("Starting....");
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH); 
 
}

void loop () {
  int a0 = analogRead(A0);
  int a1 = analogRead(A1);
  int a2 = analogRead(A2);
  int a3 = analogRead(A3);
  int a4 = analogRead(A4);
  int a5 = analogRead(A5);
  
  a0 = map(a0, 0, 1023, 0, 255);
  a1 = map(a1, 0, 1023, 0, 255);
  a2 = map(a2, 0, 1023, 0, 255);
  a3 = map(a3, 0, 1023, 0, 255);
  a4 = map(a4, 0, 1023, 0, 255);
  a5 = map(a5, 0, 1023, 0, 255);
  
  analogWrite(3, a0);
  analogWrite(5, a1);
  analogWrite(6, a2);
  analogWrite(9, a3);
  analogWrite(10, a4);
  analogWrite(11, a5);
  
  delay(10);
}

