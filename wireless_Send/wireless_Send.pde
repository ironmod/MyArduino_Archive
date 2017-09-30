int switch_1 = 2;
int switch_2 = 4;
int switch_3 = 7;
int switch_4 = 8;

void setup () {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
}

void loop () {
  if (digitalRead(2)==1){
    Serial.println("1");
  }

  delay(1000);
}

