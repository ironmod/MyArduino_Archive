/*
 Input Pullup Serial
 
 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a 
 digital input on pin 2 and prints the results to the serial monitor.
 
 The circuit: 
 * Momentary switch attached from pin 2 to ground 
 * Built-in LED on pin 13
 
 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal 
 20K-ohm resistor is pulled to 5V. This configuration causes the input to 
 read HIGH when the switch is open, and LOW when it is closed. 
 
 created 14 March 2012
 by Scott Fitzgerald
 
 http://www.arduino.cc/en/Tutorial/InputPullupSerial
 
 This example code is in the public domain
 
 */

void setup(){
  //start serial connection
  Serial.begin(9600);
  
  //Joystick inputs 
//  pinMode(2, INPUT_PULLUP); //Left
//  pinMode(4, INPUT_PULLUP); //right
//  pinMode(7, INPUT_PULLUP); //up
//  pinMode(8, INPUT_PULLUP); //down
//  pinMode(9, INPUT_PULLUP); //button1
//  pinMode(10, INPUT_PULLUP); //button2
//  pinMode(11, INPUT_PULLUP); //button 3
//  pinMode(12, INPUT_PULLUP); //button 4
  //Button inputs
  
  pinMode(2, INPUT); //Left
  pinMode(4, INPUT); //right
  pinMode(7, INPUT); //up
  pinMode(8, INPUT); //down
  pinMode(9, INPUT); //button1
  pinMode(10, INPUT); //button2
  pinMode(11, INPUT); //button 3
  pinMode(12, INPUT); //button 4
  
  //RGB LED's
  pinMode(3, OUTPUT); //Green 
  pinMode(5, OUTPUT); //Red
  pinMode(6, OUTPUT); //Blue

}

void loop(){
  //read the pushbutton value into a variable
  int button0 = digitalRead(2);
  int button1 = digitalRead(4);
  int button2 = digitalRead(7);
  int button3 = digitalRead(8);
  int button4 = digitalRead(9);
  int button5 = digitalRead(10);
  int button6 = digitalRead(11);
  int button7 = digitalRead(12);

  //Green output
  if (button0 == HIGH) {
    digitalWrite(3, LOW);
  } 
  else {
    digitalWrite(3, HIGH);
  }
  
  //Red Output
    if (button1 == HIGH) {
    digitalWrite(5, LOW);
  } 
  else {
    digitalWrite(5, HIGH);
  }
  
  //Blue output
    if (button2 == HIGH) {
    digitalWrite(6, LOW);
  } 
  else {
    digitalWrite(6, HIGH);
  }
  
  //Blue-Green output
    if (button3 == HIGH) {
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
  } 
  else {
    digitalWrite(3, HIGH);
    digitalWrite(6, HIGH);
  }
  
  //Red-Green
    if (button4 == HIGH) {
    digitalWrite(5, LOW);
    digitalWrite(3, LOW);
  } 
  else {
    digitalWrite(5, HIGH);
    digitalWrite(3, HIGH);
  }
  
  //White
    if (button5 == HIGH) {
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  } 
  else {
    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  }
  
  //Red-Blue
    if (button6 == HIGH) {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  } 
  else {
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  }
  
    if (button7 == HIGH) {
    digitalWrite(3, LOW);
  } 
  else {
    digitalWrite(3, HIGH);
  }
}



