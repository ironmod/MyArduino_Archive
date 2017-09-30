#include <Servo.h>
#include "Maxbotix.h"

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
int pwm1 = 100;
int pwm2 = 75;
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
int sw0, sw1, sw2, sw3, sw4;
Servo pan;
Servo tilt;
long microseconds=0;
int speed_select;

int range =2;
int  counter =0;
Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV);

int kickCount=0;
 int Rold=0;
 int Gold=0;
 int Bold=0;

///***************************Startup Routine**************************///
void setup(){
  setAll_OUTPUT(); //set all IO as outputs
  
  // Start the guino dashboard interface.
  // The number is your personal key for saving data. This should be unique for each sketch
  // This key should also be changed if you change the gui structure. Hence the saved data vill not match.
  gBegin(34236); 

}


//*************************Run Mode********************************//
void loop(){
  // **** Main update call for the guino
  guino_update();
  toggle_IO();  //toggle the IO outputs
  
//  //********** Read analog (comment these out if you want to control the pots on the GUI)analogMeter*****//
   analogMeter0 = analogRead(0);
   analogMeter1 = analogRead(1);
//   analogMeter2 = analogRead(2);
//   analogMeter3 = analogRead(3);
//   analogMeter4 = analogRead(4);
//   
//  //PWM Set to adjust off Analog/Potentiometer values
//  pwm1 = map(analogMeter0, 0,1023, 0, 255);
//  pwm2 = map(analogMeter1, 0,1023, 0, 180);
//  pwm3 = map(analogMeter2, 0,1023, 0, 255);
//  pwm4 = map(analogMeter3, 0,1023, 0, 255);
//  pwm5 = map(analogMeter4, 0,1023, 0, 255);
//  pwm6 = map(analogMeter5, 0,1023, 0, 255);


//************ Update Analog Values ***************//
  gUpdateValue(&analogMeter0);
  gUpdateValue(&analogMeter1);
  gUpdateValue(&analogMeter2);
  gUpdateValue(&analogMeter3);
  gUpdateValue(&analogMeter4);
  gUpdateValue(&analogMeter5); 

//*************** Update PWM Values *****************//
  gUpdateValue(&pwm1);
  gUpdateValue(&pwm2);
  gUpdateValue(&pwm3);
  gUpdateValue(&pwm4);
  gUpdateValue(&pwm5);
  gUpdateValue(&pwm6);
  gUpdateValue(&pwm7);
  
//*************** Update Discrete Values *****************//
  sw0=digitalRead(4);
  gUpdateValue(&sw0);
  gUpdateValue(&sw1);
  gUpdateValue(&sw2);
  gUpdateValue(&sw3);
  gUpdateValue(&sw4);

//*****************Range Finder ***********************//  
  range = rangeSensorAD.getRange();
  gUpdateValue(&range);

//*********Change Screen Red During Missle Launch*******//
  if(digitalRead(8)==HIGH)
    {
       if(kickCount == 0)
       {
         Rold=r;
         Gold=g;
         Bold=b;
       }
      r=250;
      g=0;
      b=0;
     gSetColor(r,g,b);
     kickCount=1;
    }
  else if (digitalRead(8)==LOW && kickCount==1)
  {
    r = Rold;
    g = Gold;
    b = Bold;
    gSetColor(r,g,b);
    kickCount=0;
  }
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




