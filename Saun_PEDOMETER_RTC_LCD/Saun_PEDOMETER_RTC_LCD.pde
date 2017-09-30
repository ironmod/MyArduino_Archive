/*
                                                             .......~..         
                                                             ......$...         
                                                             ....I$Z...         
                                                          ......Z$$~.           
                                                           ...:$$$$..           
                                                          ...7$Z:Z$..           
                                                          .:$$:.,$,..           
     .....................................................$$+...?Z..............
 .:::~============I?????????????????????IIIIIIIIIIIIIII?I$ZIIII7$77777777I7II77=
  .....................................................+Z,......$,,,,:,=$$$Z~...
                                             .........Z:..... .:Z...:$$$I,...   
                                             ...  ..==.........7~.$$$+.......   
                                                ...7...... ....Z$$I.......      
                                              ...,..........=7$7..              
                                              ...........+Z7..~,.               
                                              ........,7Z:....I..               
                                              .....,7I.. .....I..               
                                        .........$~...............              
                                     ........,7...        . .=..                
                                     ......~~.....        . .=..                
                                        :....             ......                
                                         ....                                
                                                                                

.____    ________  _________  ____  __.___ _________________________________   
|    |   \_____  \ \_   ___ \|    |/ _/   |   \_   _____/\_   _____/\______ \  
|    |    /   |   \/    \  \/|      </    ~    \    __)_  |    __)_  |    |  \ 
|    |___/    |    \     \___|    |  \    Y    /        \ |        \ |    `   \
|_______ \_______  /\______  /____|__ \___|_  /_______  //_______  //_______  /
        \/       \/        \/        \/     \/        \/         \/         \/ 
   _____      _____ _____________________.___ _______   
  /     \    /  _  \\______   \__    ___/|   |\      \  
 /  \ /  \  /  /_\  \|       _/ |    |   |   |/   |   \ 
/    Y    \/    |    \    |   \ |    |   |   /    |    \
\____|__  /\____|__  /____|_  / |____|   |___\____|__  /	(ish)
        \/         \/       \/                       \/ 
(unofficial of course) Firmware to a "healthier" "smarter" pedometer 
Designed by the infamous iRonBit 
*/
#include <Servo.h> 
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
#include <TKLCD.h>
#include <EEPROM.h>

TKLCD_Serial lcd = TKLCD_Serial();
RTC_DS1307 rtc;


///****************************************************************///
//                        Parameters/Variables                     ///
//*****************************************************************///

//Servo parameters
	Servo PAN_SERVO;  
	Servo TILT_SERVO;
	int PAN_ANGLE		= 0;
	int TILT_ANGLE		= 0;
	int MAX_ANGLE 		= 180;
	int MIN_ANGLE		= 0;
	int  SPEED 			= 5;
	int pos         	= 0;
//RTC Variables
	int hour_start 		= 0;
	int hour_stop		= 0;
	int minute_start 	= 0;
	int minute_stop	 	= 0;
	int RTC_hour		= 0;
	int RTC_minute		= 0;
	int RTC_seconds 	= 0;
//LCD Menu && EEPROM Variables
	int button_counter 	= 0;
	int menu_screen 	= 0;
	int num_cases		= 6;
	int analogInput 	= 0;
	int LCD_MENU_BTN 	= 2;
	int LCD_POT			= A0;

///****************************************************************///
//                        Startup Routine                          ///
//*****************************************************************///
void setup() 
{ 

//LCD and Serial Init
	Serial.begin(9600);
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(128);

	Serial.write("                "); // clear display
	Serial.write("                ");

	delay(1000);
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(128);
	Serial.write("Staying Healthy and Smart the ironbit way!");
  
//IO Init
	pinMode(LCD_MENU_BTN, INPUT_PULLUP);  
	pinMode(A2, OUTPUT);	//These are just because I am lazy
	pinMode(A3, OUTPUT);	//and it allows me to power the RTC
	digitalWrite(A2, LOW);	//straight from the analog pins
	digitalWrite(A3, HIGH);	//and not have to use jumper wire

//Load the EEPROM values
	hour_start 	 	= EEPROM.read(0);
	minute_start 	= EEPROM.read(1);
	hour_stop 		= EEPROM.read(2);
	minute_stop		= EEPROM.read(3);
	SPEED			= EEPROM.read(4);

//Initialize Servos
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
	RTC_hour	 = now.hour();
	RTC_minute 	 = now.minute();
	RTC_seconds	 = now.second();

//Used for Navigating through the menu
	if(digitalRead(LCD_MENU_BTN)==LOW)
	{
		button_counter++;
		Serial.write("                "); // clear display
		Serial.write("                ");
	}
	
//Reset the Menu after user has gone through
	if(button_counter > num_cases)
	{
		button_counter = 0;
		Serial.write("                "); // clear display
		Serial.write("                ");
	}
	
	menu_screen = button_counter; //Probably not really necesary but using for the FSM
	analogInput = analogRead(LCD_POT);
		
/************************ LCD Menu **********************************/
	switch(menu_screen)
	{
		case 0:
			Serial.write(254); // move cursor to beginning of first line
			Serial.write(128);
  			Serial.write("Time ");
			
			if(RTC_hour<10)
				Serial.write("0"); //fixes the overlay issue
			Serial.print(RTC_hour);
			Serial.write(":");
			
			if(RTC_minute<10)
				Serial.write("0");
			Serial.print(RTC_minute);
			
			Serial.write(".");
			
			if(RTC_seconds<10)
				Serial.write("0");
			Serial.print(RTC_seconds);
			
			Serial.write(254);
			Serial.write(192);
			Serial.print("Run @ ");
			Serial.print(hour_start);
			Serial.write(":");
			Serial.print(minute_start);
			break;
			
		case 1:
			Serial.write(254); // move cursor to beginning of first line
			Serial.write(128);
 			Serial.write("Hour to start at? ");
			Serial.write(254);
			Serial.write(192);
			analogInput = analogRead(LCD_POT);
			analogInput = map(analogInput, 0, 1023, 0, 24);
			hour_start = analogInput;
			EEPROM.write(0, hour_start);
			if(analogInput<10)
				Serial.write("0");
			Serial.print(hour_start);
			break;
			
		case 2:
			Serial.write(254); // move cursor to beginning of first line
			Serial.write(128);
 			Serial.write("Minute to start? ");
			Serial.write(254);
			Serial.write(192);
			analogInput = analogRead(LCD_POT);
			analogInput = map(analogInput, 0, 1023, 0, 60);
			minute_start = analogInput;
			EEPROM.write(1, minute_start);
			if(analogInput<10)
				Serial.write("0");
			Serial.print(minute_start);
			break;
			
		case 3:
			Serial.write(254); // move cursor to beginning of first line
			Serial.write(128);
 			Serial.write("Hour to end at? ");
			Serial.write(254);
			Serial.write(192);
			analogInput = analogRead(LCD_POT);
			analogInput = map(analogInput, 0, 1023, 0, 24);
			hour_stop = analogInput;
			EEPROM.write(2, hour_stop);
			if(analogInput<10)
				Serial.write("0");
			Serial.print(hour_stop);
			break;
			
		case 4:
			Serial.write(254); // move cursor to beginning of first line
			Serial.write(128);
 			Serial.write("Minute to end? ");
			Serial.write(254);
			Serial.write(192);
			analogInput = analogRead(LCD_POT);
			analogInput = map(analogInput, 0, 1023, 0, 60);
			minute_stop = analogInput;
			EEPROM.write(3, minute_stop);
			if(analogInput<10)
				Serial.write("0");
			Serial.print(minute_stop);
			break;
			
		case 5:
			Serial.write(254); // move cursor to beginning of first line
			Serial.write(128);
 			Serial.write("Speed (0-25ms): ");
			Serial.write(254);
			Serial.write(192);
			analogInput = analogRead(LCD_POT);
			analogInput = map(analogInput, 0, 1023, 0, 25);
			SPEED = analogInput;
			EEPROM.write(4, SPEED);
			if(analogInput<10)
				Serial.write("0");
			Serial.print(SPEED);
			break;
			
		case 6:
			Serial.write(254); // move cursor to beginning of first line
			Serial.write(128);
 			Serial.write("Cal. Successful");
			Serial.write(254);
			Serial.write(192);
			Serial.write("Stay Healthy LM!");
			
	 }//end fsm
	 

//*************************** Automode *******************************//
	if ((hour_start==RTC_hour) && (minute_start==RTC_minute) && (menu_screen==0) 
			&& (digitalRead(LCD_MENU_BTN)==HIGH))
	{
		RTC_hour = now.hour();
		RTC_minute = now.minute();
		
		//Kill the mode once time has been reached
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
				delay(SPEED);                       //Speed (delay)
			  } 
			  
			//Reverse the Servo Position
			  for(pos = MAX_ANGLE; pos>=MIN_ANGLE; pos-=1)     
			  {              
				PAN_SERVO.write(pos);              
				TILT_SERVO.write(pos);
				delay(SPEED);                       // Speed(delay)
			  }
			  
			}//end RTC while
	}//end automode
	
	delay(200);
} 

