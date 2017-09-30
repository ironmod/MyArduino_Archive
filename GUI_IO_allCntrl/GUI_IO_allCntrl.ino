
int amplitude = 20;
int width = 0;
int graphValue = 0;
int analogMeter0 = 0;
int analogMeter2 = 0;
int analogMeter3 = 0;
int analogMeter4 = 0;
int analogMeter5 = 0;
int analogMeter1 = 0;
float angle = 0;
int pwm1 = 3;
int pwm2 = 5;
int pwm3 = 6;
int pwm4 = 9;
int pwm5 = 10; 
int pwm6 = 11;
int pwm7 = 13;

int r = 0;
int g = 0;
int b = 0;
int rotaryRID,rotaryGID,rotaryBID;

int button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12, button13;

void setup(){
  setAll_OUTPUT();
  // Start the guino dashboard interface.
  // The number is your personal key for saving data. This should be unique for each sketch
  // This key should also be changed if you change the gui structure. Hence the saved data vill not match.
  gBegin(34236); 

}

void loop(){
  // **** Main update call for the guino
  guino_update();
  toggle_IO();  
  
  // Read analog
   analogMeter0 = analogRead(0);
   analogMeter1 = analogRead(1);
   analogMeter2 = analogRead(2);
   analogMeter3 = analogRead(3);
   analogMeter4 = analogRead(4);
   
  //PWM Set to adjust off Analog/Potentiometer values
  pwm1 = map(analogMeter0, 0,1023, 0, 255);
  pwm2 = map(analogMeter1, 0,1023, 0, 255);
  pwm3 = map(analogMeter2, 0,1023, 0, 255);
  pwm4 = map(analogMeter3, 0,1023, 0, 255);
  pwm5 = map(analogMeter4, 0,1023, 0, 255);
  pwm6 = map(analogMeter5, 0,1023, 0, 255);
  
  
  
  // Update Analog values
  gUpdateValue(&analogMeter0);
  gUpdateValue(&analogMeter1);
  gUpdateValue(&analogMeter2);
  gUpdateValue(&analogMeter3);
  gUpdateValue(&analogMeter4);
  gUpdateValue(&analogMeter5); 

  //Update PWM Values
  gUpdateValue(&pwm1);
  gUpdateValue(&pwm2);
  gUpdateValue(&pwm3);
  gUpdateValue(&pwm4);
  gUpdateValue(&pwm5);
  gUpdateValue(&pwm6);
  gUpdateValue(&pwm7);
}

// This is where you setup your interface 
void gInit()
{
//Analog Input Graphs
  gAddLabel("Analog Inputs A0 A1 A2",1);
  gAddSpacer(1); 
  gAddMovingGraph("A0",0,1023, &analogMeter0, 10);
  gAddRotarySlider(0,1023,"A0",&analogMeter0);
  gAddMovingGraph("A1",0,1023, &analogMeter1, 10);
  gAddRotarySlider(0,1023,"A1",&analogMeter1);
  gAddMovingGraph("A2",0,1023, &analogMeter2, 10);
  gAddRotarySlider(0,1023,"A2",&analogMeter2);
  gAddColumn();
  
  gAddLabel("Analog Inputs A3 A3 A5",1);
  gAddSpacer(1);  
  
  gAddMovingGraph("A3",0,1023, &analogMeter3, 10);
  gAddRotarySlider(0,1023,"A3",&analogMeter3);
  gAddMovingGraph("A4",0,1023, &analogMeter4, 10);
  gAddRotarySlider(0,1023,"A4",&analogMeter4); 
  gAddMovingGraph("A5 ",0,1023, &analogMeter5, 10);
  gAddRotarySlider(0,1023,"A5 ",&analogMeter5);

//Set PWM Output Graphs
  gAddColumn();
  gAddLabel("PWM Outputs",1);
  gAddSpacer(1); 
 
  gAddSlider(0,255,"Pin 3 PWM",&pwm1);
  gAddSlider(0,255,"Pin 5 PWM ",&pwm2);
  gAddSlider(0,255,"Pin 6 PWM ",&pwm3);
  gAddSlider(0,255,"Pin 9 PWM ",&pwm4);
  gAddSlider(0,255,"Pin 10 PWM ",&pwm5);
  gAddSlider(0,255,"Pin 11 PWM ",&pwm6); 
  gAddSlider(0,255,"Pin 13 PWM",&pwm7);
  
//Set Buttons
  gAddSpacer(2);
  gAddLabel("Digital IO Control Buttons",1);
  gAddSpacer(1);
  gAddToggle("Digital Output 1 (TX)", &button1); 
  gAddToggle("Digital Output 2 (RX)", &button2); 
  gAddToggle("Digital Output 3 (PWM)", &button3); 
  gAddToggle("Digital Output 4", &button4); 
  gAddToggle("Digital Output 5 (PWM)", &button5); 
  gAddToggle("Digital Output 6", &button6); 
  gAddToggle("Digital Output 7", &button7); 
  gAddToggle("Digital Output 8", &button8); 
  gAddToggle("Digital Output 9 (PWM)", &button9); 
  gAddToggle("Digital Output 10 (PWM)", &button10); 
  gAddToggle("Digital Output 11 (PWM)", &button11); 
  gAddToggle("Digital Output 12", &button12); 
  gAddToggle("Digital Output 13 (PWM)", &button13); 
    
//Set Color Wheels
  gAddColumn();
  gAddSpacer(1);
  gAddLabel("RGB Color Wheel", 1);
  gAddSpacer(1);
  
  rotaryRID = gAddRotarySlider(0,255,"R",&r);
  rotaryGID = gAddRotarySlider(0,255,"G",&g);
  rotaryBID = gAddRotarySlider(0,255,"B",&b);  
 
}

// Method called everytime a button has been pressed in the interface.
void gButtonPressed(int id)
{

}

void gItemUpdated(int id)
{
  if(rotaryRID == id || rotaryGID == id || rotaryBID == id)
  {
    gSetColor(r,g,b);
  }
// if(rotaryA0 == id)
   
}

//Set States of the Digital IO
void toggle_IO(){
    //Digital IO Update
  if(button1)
    digitalWrite(1, HIGH);
  else digitalWrite(1, LOW);
  
  if(button2)
    digitalWrite(2, HIGH);
  else digitalWrite(2, LOW);
  
  if(button3)
    digitalWrite(3, HIGH);
  else digitalWrite(3, LOW);
  
  if(button4)
    digitalWrite(4, HIGH);
  else digitalWrite(4, LOW);
  
  if(button5)
    digitalWrite(5, HIGH);
  else digitalWrite(5, LOW);
  
  if(button5)
    digitalWrite(6, HIGH);
  else digitalWrite(6, LOW);
  
  if(button7)
    digitalWrite(7, HIGH);
  else digitalWrite(7, LOW);
  
  if(button8)
    digitalWrite(8, HIGH);
  else digitalWrite(8, LOW);
  
  if(button9)
    digitalWrite(9, HIGH);
  else digitalWrite(9, LOW);
  
  if(button10)
    digitalWrite(10, HIGH);
  else digitalWrite(10, LOW);
 
  if(button11)
    digitalWrite(11, HIGH);
  else digitalWrite(11, LOW);
  
  if(button12)
    digitalWrite(12, HIGH);
  else digitalWrite(12, LOW);
  
  if(button13)
    digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);
  
}

//Set All Pins as Ouputs;
void setAll_OUTPUT() {
    pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}


