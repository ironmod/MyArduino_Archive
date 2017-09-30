#include <Servo.h> 
 #include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
Servo PAN_SERVO;  
Servo TILT_SERVO;
int PAN_ANGLE	= 0;
int TILT_ANGLE	= 0;
int MAX_ANGLE 	= 180;
int MIN_ANGLE	= 0;
int  SPEED 		= 5;
int start_btn	= 0;
int manual_ctrl	= 0;
int red 		= 0;
int blue  		= 150;
int green		= 120;
int pos         = 0;
int rotaryRID,rotaryGID,rotaryBID;
int hour_start 	= 15;
int hour_stop	= 15;
int minute_start = 54;
int minute_stop = 56;
int RTC_hour = 0;
int RTC_minute = 0;
//int flexLabelId = 0;

///****************************************************************///
//                        Startup Routine                          ///
//*****************************************************************///
void setup() 
{ 
pinMode(A2, OUTPUT);
pinMode(A3, OUTPUT);
digitalWrite(A2, LOW);
digitalWrite(A3, HIGH);


//Servos and GUINO Setup
	PAN_SERVO.attach(10);  // attaches the servo on pin 9 to the servo object 
	TILT_SERVO.attach(11);
	gBegin(34236); 
	delay(2000);
	//RTC Setup
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();
  
	gSetColor(red,green,blue);
} 
 
//*****************************************************************///
//                          Run Mode                                //
//*****************************************************************/// 
void loop() 
{ 

	DateTime now = rtc.now();
  guino_update(); //Update the GUINO Dashboard (GUI)
	RTC_hour = now.hour();
	RTC_minute = now.minute();
	gUpdateValue(&RTC_hour);
	gUpdateValue(&RTC_minute);
//***************Automode****************************//
	if (start_btn && !manual_ctrl && (hour_start==RTC_hour) && (minute_start==RTC_minute))
	{
		RTC_hour = now.hour();
		RTC_minute = now.minute();
		
		if( (minute_stop!=RTC_minute))
		{	
			//update RTC values for while loop
			RTC_hour = now.hour();
			RTC_minute = now.minute();
			
			//Start the Servos
			  for(pos = MIN_ANGLE; pos < MAX_ANGLE; pos += 1) 
			  {
				PAN_SERVO.write(pos);              
				TILT_SERVO.write(pos);
				RTC_hour = now.hour();
				guino_update(); //Update the GUINO Dashboard (GUI)
				gUpdateValue(&pos);
				gUpdateValue(&RTC_hour);
				delay(SPEED);                       //Speed (delay)
			  } 
			  
			//Reverse the Servo Position
			  for(pos = MAX_ANGLE; pos>=MIN_ANGLE; pos-=1)     
			  {              
				PAN_SERVO.write(pos);              
				TILT_SERVO.write(pos);
				guino_update(); //Update the GUINO Dashboard (GUI)
				RTC_hour = now.hour();
				gUpdateValue(&pos); 
				delay(SPEED);                       // Speed(delay)
			  }
			  
			}//end RTC while
	}//end automode
	
//***************Manual Mode****************************//
	else if(manual_ctrl && !start_btn)
	{
		PAN_SERVO.write(PAN_ANGLE);              
		TILT_SERVO.write(TILT_ANGLE);
	}
	delay(50);
  
} 

//*****************************************************************///
//                 GUINO Dashboard Parameters                       //
//*****************************************************************/// 

void gInit ()
{
//***************Servo parameters****************************//
  gAddSpacer(1);
  gAddLabel("Servo Controller Parameters", 1);
  gAddSpacer(1);
  gAddSlider(0,180,"PAN",&PAN_ANGLE);
  gAddSlider(0,180,"TILT",&TILT_ANGLE);
  gAddSlider(0,180,"MAX Servo Angle",	&MAX_ANGLE);
  gAddSlider(0,180,"MIN Servo Angle",	&MIN_ANGLE);
  gAddRotarySlider(0,25,"Speed",		&SPEED);
  gAddMovingGraph("Position", 0, 255, &pos, 15);
  gAddToggle("Start", &start_btn);
  gAddToggle("Manual Servo Control", &manual_ctrl);
  gAddSlider(0,24,"Hour Start Time",	&hour_start);
  gAddSlider(0,24,"Hour Stop Time",	&hour_stop);
  gAddSlider(0,60,"Minute Start Time",	&minute_start);
  gAddSlider(0,60,"Hour Stop Time",	&minute_stop);
  gAddSlider(0, 24, "RTC_HOUR", &RTC_hour);
  gAddSlider(0, 60, "RTC_Minute", &RTC_minute);
//***************Color Choser****************************//
  gAddColumn();
  gAddSpacer(1);
  gAddLabel("RGB Color Wheel", 1);
  gAddSpacer(1);
  
  rotaryRID = gAddRotarySlider(0,255,"R",&red);
  rotaryGID = gAddRotarySlider(0,255,"G",&green);
  rotaryBID = gAddRotarySlider(0,255,"B",&blue); 
  
}


// Method called everytime a button has been pressed in the interface.
void gButtonPressed(int id)
{

}

void gItemUpdated(int id)
{

  if(rotaryRID == id || rotaryGID == id || rotaryBID == id)
  {  
    gSetColor(red,green,blue);
  }
 
}
