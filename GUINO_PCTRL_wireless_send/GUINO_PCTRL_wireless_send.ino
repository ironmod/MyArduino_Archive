#include <Servo.h>
//#include "Maxbotix.h"
#include <Math.h> 
#include <SoftwareSerial.h>

//*************** IO Monitor Variables***********//
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
int pwm2 = 130;
int pwm3 = 6;
int pwm4 = 9;
int pwm5 = 10; 
int pwm6 = 11;
int pwm7 = 13;
int r = 0;
int g = 50;
int b = 125;
int rotaryRID,rotaryGID,rotaryBID;

//*********** GUI Button Variables **********//
int button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12, button13;
int sw0, sw1, sw2, sw3, sw4;

//*********** Turret Variables *************//
int calibrateTurret;
//Servo pan;
//Servo tilt;
int tilt = 0;
int pan  = 0;
int tiltOld = 0;
int panOld = 0;
long microseconds=0;
int speed_select;
int i=0;
int thresh=2;
int scanDelay=400;
int scanRate=400;

//********** Range Variables *************//
int range =2;
int  counter =0;
//Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV);
int r0=0, r1=0, r2=0, r3=0, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17;
int r0old=0, r1old=0, r2old=0, r3old=0, r4old=0, r5old=0, r6old=0, r7old=0, r8old=0, r9old=0, r10old=0, r11old=0, r12old=0, r13old=0, r14old=0, r15old=0, r16old=0, r17old=0;
int rangeVal[] =
{ r0old, r1old, r2old, r3old, r4old, r5old, r6old, r7old, r8old, r9old, r10old, r11old, r12old, r13old, r14old, r15old, r16old, r17old};

//***********Motor Control Variables*******//
int forward, left, right, reverse;
int speedCtrl=0;
int speedOld=0;
//*********** Color Choser Variables ************//
int kickCount=0;
 int Rold=0;
 int Gold=0;
 int Bold=0;
 
SoftwareSerial mySerial(10, 11); // RX, TX

///****************************************************************///
//                        Startup Routine                          ///
//*****************************************************************///
void setup(){
  setAll_OUTPUT(); //set all IO as outputs
  mySerial.begin(115200);
  mySerial.println("Hello, world?");
  // Start the guino dashboard interface.
  // The number is your personal key for saving data. This should be unique for each sketch
  gBegin(34236); 
  delay(2000);
}


//*****************************************************************///
//                    Run Mode                                      //
//*****************************************************************///
void loop(){
  // **** Main update call for the guino
  guino_update();
  toggle_IO();  //toggle the IO outputs

//  //********** Read analog (comment these out if you want to control the pots on the GUI)analogMeter*****//
   analogMeter0 = analogRead(0);
   analogMeter1 = analogRead(1);
   analogMeter2 = analogRead(2);
//   analogMeter3 = analogRead(3);
//   analogMeter4 = analogRead(4);
  

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
  forward=digitalRead(4);
  left = digitalRead(2);
  right = digitalRead(8);
  reverse = digitalRead(7);
  gUpdateValue(&forward);
  gUpdateValue(&left);
  gUpdateValue(&right);
  gUpdateValue(&reverse);

  
////*************** Turret Calibration *****************//


////*************** Armed Servo Sweep *****************//

   tilt = analogRead(A1);
   pan = analogRead(A2);
   tilt = map(tilt, 0, 1023, 0, 255);
   pan = map(pan, 0, 1023, 0, 255);
   if (panOld!=pan) 
   {
     gUpdateValue(&pan);
     mySerial.println("P" + pan);
  //   mySerial.println(pan);
   }
   
   if(panOld!=pan)
   { 
     gUpdateValue(&tilt);
     mySerial.println("T" + tilt);
  //   mySerial.println(tilt);
   }
 
  panOld = pan;
  tiltOld = tilt; 
  
////*****************Range Finder ***********************//  
//  range = rangeSensorAD.getRange();
//  range=range/2.54;
//  gUpdateValue(&range);

//***************Motor Controller ********************//
  MotorControl();

  
//*********Change Screen Red During Missle Launch*******//
//  if(digitalRead(8)==HIGH)
//    {
//       if(kickCount == 0)
//       {
//         Rold=r;
//         Gold=g;
//         Bold=b;
//       }
//      r=250;
//      g=0;
//      b=0;
//     gSetColor(r,g,b);
//     kickCount=1;
//    }
//  else if (digitalRead(8)==LOW && kickCount==1)
//  {
//    r = Rold;
//    g = Gold;
//    b = Bold;
//    gSetColor(r,g,b);
//    kickCount=0;
//  }
  
  delay(10);
  
} //end void loop



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




