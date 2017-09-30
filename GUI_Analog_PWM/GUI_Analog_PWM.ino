
// Dummy example variables

int amplitude = 20;
int width = 0;
int graphValue = 0;
int potMeter0 = 0;
int potMeter2 = 0;
int potMeter3 = 0;
int potMeter4 = 0;
int potMeter5 = 0;
int potMeter1 = 0;
float angle = 0;
int pwm1 = 3;
int pwm2 = 5;
int pwm3 = 6;
int pwm4 = 9;
int pwm5 = 10; 
int pwm6 = 11;

int r = 0;
int g = 75;
int b = 110;

void setup(){
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  // Start the guino dashboard interface.
  // The number is your personal key for saving data. This should be unique for each sketch
  // This key should also be changed if you change the gui structure. Hence the saved data vill not match.
  gBegin(34236); 
}

void loop(){
  // **** Main update call for the guino
  guino_update();

  // Read analog
   potMeter0 = analogRead(0);
   potMeter1 = analogRead(1);
   potMeter2 = analogRead(2);
   potMeter3 = analogRead(3);
   potMeter4 = analogRead(4);
  // potMeter5 = analogRead(5);
//  r = map(potMeter0, 0,1023, 0, 255);
//  g = map(potMeter1, 0,1023, 0, 255);
//  b = map(potMeter2, 0,1023, 0, 255);

  //PWM Set
  pwm1 = map(potMeter0, 0,1023, 0, 255);
  pwm2 = map(potMeter1, 0,1023, 0, 255);
  pwm3 = map(potMeter2, 0,1023, 0, 255);
  pwm4 = map(potMeter3, 0,1023, 0, 255);
  pwm5 = map(potMeter4, 0,1023, 0, 255);
  pwm6 = map(potMeter5, 0,1023, 0, 255);
  
  // Update Analog values
  gUpdateValue(&potMeter0);
  gUpdateValue(&potMeter1);
  gUpdateValue(&potMeter2);
  gUpdateValue(&potMeter3);
  gUpdateValue(&potMeter4);
 // gUpdateValue(&potMeter5); 

  //Update PWM Values
  gUpdateValue(&pwm1);
  gUpdateValue(&pwm2);
  gUpdateValue(&pwm3);
  gUpdateValue(&pwm4);
  gUpdateValue(&pwm5);
  gUpdateValue(&pwm6);
  
//  gSetColor(r, g, b);  
}

// This is where you setup your interface 
void gInit()
{
  gAddLabel("Analog Inputs",2);
  gAddSpacer(1); 
 
  //Analog Input Graphs
  gAddMovingGraph("POT0",0,1023, &potMeter0, 7);
  gAddSlider(0,1023,"POT0",&potMeter0);
  
  gAddMovingGraph("POT1",0,1023, &potMeter1, 7);
  gAddSlider(0,1023,"POT1",&potMeter1);
  
  gAddMovingGraph("POT2",0,1023, &potMeter2, 7);
  gAddSlider(0,1023,"POT2",&potMeter2);

  gAddMovingGraph("POT3",0,1023, &potMeter3, 7);
  gAddSlider(0,1023,"POT3",&potMeter3);
  
  gAddMovingGraph("POT4",0,1023, &potMeter4, 7);
  gAddSlider(0,1023,"POT4",&potMeter4);
  
  gAddMovingGraph("POT5 ",0,1023, &potMeter5, 7);
  gAddSlider(0,1023,"POT5 ",&potMeter5);
  
  //Set PWM Output Graphs
  gAddColumn(); 
  gAddLabel("PWM Outputs",2);
  gAddSpacer(1); 
  
  gAddSlider(0,255,"Pin 3 PWM",&pwm1);
  gAddSlider(0,255,"Pin 5 PWM ",&pwm2);
  gAddSlider(0,255,"Pin 6 PWM ",&pwm3);
  gAddSlider(0,255,"Pin 9 PWM ",&pwm4);
  gAddSlider(0,255,"Pin 10 PWM ",&pwm5);
  gAddSlider(0,255,"Pin 11 PWM ",&pwm6);
  
      // Add more stuff here.
  gSetColor(r,g,b); // Set the color of the gui interface. 
}

// Method called everytime a button has been pressed in the interface.
void gButtonPressed(int id)
{
 
}

void gItemUpdated(int id)
{

}








