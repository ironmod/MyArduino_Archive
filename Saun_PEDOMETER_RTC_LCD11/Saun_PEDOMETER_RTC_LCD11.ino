#include <Servo.h> 
 #include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
#include <TKLCD.h>


TKLCD_Serial lcd = TKLCD_Serial();
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
int hour_start 	= 15;
int hour_stop	= 15;
int minute_start = 42;
int minute_stop = 43;
int RTC_hour = 0;
int RTC_minute = 0;


///****************************************************************///
//                        Startup Routine                          ///
//*****************************************************************///
void setup() 
{ 
  lcd.begin();
  lcd.clear();
  lcd.print("Hello World);
  
pinMode(A2, OUTPUT);
pinMode(A3, OUTPUT);
digitalWrite(A2, LOW);
digitalWrite(A3, HIGH);


//Servos and GUINO Setup
	PAN_SERVO.attach(10);  // attaches the servo on pin 9 to the servo object 
	TILT_SERVO.attach(11);
	delay(2000);
	//RTC Setup
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();
  
} 
 
//*****************************************************************///
//                          Run Mode                                //
//*****************************************************************/// 
void loop() 
{ 

	DateTime now = rtc.now();
	RTC_hour = now.hour();
	RTC_minute = now.minute();

//***************Automode****************************//
	if ((hour_start==RTC_hour) && (minute_start==RTC_minute))
	{
		//while((hour_stop!=RTC_hour) && (minute_stop!=RTC_minute))
		//{	
			//update RTC values for while loop
			RTC_hour = now.hour();
			RTC_minute = now.minute();
			
			//Start the Servos
			  for(pos = MIN_ANGLE; pos < MAX_ANGLE; pos += 1) 
			  {
				PAN_SERVO.write(pos);              
				TILT_SERVO.write(pos);
				RTC_hour = now.hour();
					delay(SPEED);                       //Speed (delay)
			  } 
			  
			//Reverse the Servo Position
			  for(pos = MAX_ANGLE; pos>=MIN_ANGLE; pos-=1)     
			  {              
				PAN_SERVO.write(pos);              
				TILT_SERVO.write(pos);
				RTC_hour = now.hour();
				delay(SPEED);                       // Speed(delay)
			  }
			  
			//}//end RTC while
	}//end automode
	
//***************Manual Mode****************************//
/*	else if(manual_ctrl && !start_btn)
	{
		PAN_SERVO.write(PAN_ANGLE);              
		TILT_SERVO.write(TILT_ANGLE);
	} 
	*/
} 


