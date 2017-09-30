
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
int pwm1 = 0;
int pwm2 = 0;
int pwm3 = 0;
int pwm4 = 0;
int pwm5 = 0; 
int pwm6 = 0;
int pwm7 = 0;



int r = 0;
int g = 50;
int b = 50;
int rotaryRID,rotaryGID,rotaryBID;

int button0, button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12, button13;

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
  
//  // Read analog (comment these out if you want to control the pots on the GUI)analogMeter
//   analogMeter0 = analogRead(0);
//   analogMeter1 = analogRead(1);
//   analogMeter2 = analogRead(2);
//   analogMeter3 = analogRead(3);
//   analogMeter4 = analogRead(4);
//   
  //PWM Set to adjust off Analog/Potentiometer values
  pwm1 = map(analogMeter0, 0,1023, 0, 255);
   analogWrite(3, pwm1);
  pwm2 = map(analogMeter1, 0,1023, 0, 255);
   analogWrite(5, pwm2);
  pwm3 = map(analogMeter2, 0,1023, 0, 255);
    analogWrite(6, pwm3);
  pwm4 = map(analogMeter3, 0,1023, 0, 255);
   analogWrite(10, pwm4);    
  pwm5 = map(analogMeter4, 0,1023, 0, 255);
    analogWrite(9, pwm5);
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




