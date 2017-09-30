//Set All Pins as Ouputs;
void setAll_OUTPUT() {
  pinMode(2, INPUT_PULLUP);
  //pinMode(3, INPUT_PULLUP);
    pinMode(4, OUTPUT);
  //pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT);
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(2, HIGH);
//  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
//  digitalWrite(5, HIGH);
//  digitalWrite(6, HIGH);
  
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}
