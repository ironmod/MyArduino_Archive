//Set All Pins as Ouputs;
void setAll_OUTPUT() {
  pinMode(2, OUTPUT);    //PIR SENSOR
  pinMode(3, OUTPUT);    //R2 OUTPUT
  pinMode(4, INPUT);     
  pinMode(5, OUTPUT);    //G2 OUTPUT
  pinMode(6, OUTPUT);    //B2 OUTPUT
  pinMode(7, OUTPUT);    
  pinMode(8, INPUT);      //RGB2 Mode
  pinMode(9, INPUT);      //Fading mode Switch
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
//  digitalWrite(4, LOW);  
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
//  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  //digitalWrite(13, HIGH);
}
