
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
  setAll_OUTPUT(); //set all IO as outputs
  
  // Start the guino dashboard interface.
  // The number is your personal key for saving data. This should be unique for each sketch
  // This key should also be changed if you change the gui structure. Hence the saved data vill not match.
  gBegin(34236); 

}

void loop(){
  // **** Main update call for the guino
  guino_update();
  toggle_IO();  //toggle the IO outputs
  
  // Read analog (comment these out if you want to control the pots on the GUI)analogMeter
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
 
}




