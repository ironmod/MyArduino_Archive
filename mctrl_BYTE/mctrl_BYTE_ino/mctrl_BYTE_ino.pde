#include "math.h"
#include <IOShieldOled.h>
#include <Wprogram.h>

#define OLED IOShieldOledClass

OLED oled;
//Motor Driver Left
int IN1 		= 2;
int IN2 		= 4;
int IN3 		= 6;
int IN4 		= 7;
//Motor Driver Right
int IN5 		= 8;
int IN6 		= 9;
int IN7 		= 12;
int IN8 		= 13;
//Motor PWM Pins
int M1_SPEED 	= 3;
int M2_SPEED	= 10;
int M3_SPEED 	= 5;
int M4_SPEED	= 11;
int M_ALL_PWM 	= 0;
//Motor PWM Values
int M1_PWM 		= 0;
int M2_PWM 		= 0;
int M3_PWM 		= 0;
int M4_PWM 		= 0;

int verify = 0;
int i = 0;

int M_SELECT = 0; //Select Which Motor to change speed
int M_DIR[] = { 26, 27, 28, 29, 30, 31, 32, 33 };
int M_SPD[] = { 3, 10, 5, 11 };
int data_read = B10101101;
boolean DEBUG = true;

boolean clear_screen = false;

void setup ()
{
	Serial.begin(9600);

	OLED_INIT();
	OLED_UPDATE();
//Set all pins as OUTPUTS
	for (i=0; i<8; i++)
		{
			pinMode(M_DIR[i], OUTPUT);
		}
	

	
}//end setup

void loop ()
{
	while(Serial.available())
	{
		data_read = Serial.read();
		switch(data_read)
		{
		//Assign Motor Direction
			case 'D':
				if(DEBUG) Serial.println("Motors");// DEBUG
				
				data_read = Serial.read();	
				for (i=0; i<8; i++)
				{
					digitalWrite(M_DIR[i], bitRead(data_read, i));
					if(DEBUG) Serial.print(bitRead(data_read, i)); //DEBUG
				}
				if(DEBUG) Serial.println();//DEBUG
			break;
		
		//Assign Motor Speeds Individually 
			case '1':
				M1_PWM = Serial.parseInt();
				M1_PWM = M1_PWM - '0';
				M1_PWM = constrain(M1_PWM, 0 ,255);
				analogWrite(M1_SPEED, M1_PWM);
				Serial.println(M1_PWM);
			break;
			
			case '2':
				M2_PWM = Serial.read();
				M2_PWM = constrain(M2_PWM, 0 ,255);
				analogWrite(M2_SPEED, M2_PWM);
			break;
			
			case '3':
				M3_PWM = (int)Serial.read();
				M3_PWM = constrain(M3_PWM, 0 ,255);
				analogWrite(M3_SPEED, M3_PWM);
			break;
			
			case '4':
				M4_PWM = (int)Serial.read();
				M4_PWM = constrain(M4_PWM, 0 ,255);
				analogWrite(M4_SPEED, M4_PWM);
			break;
		
		//Use the same speed for all motors
			case '5':
				M_ALL_PWM = (int)Serial.read();
				M_ALL_PWM = constrain(M_ALL_PWM, 0 ,255);
				analogWrite(M1_SPEED, M_ALL_PWM);
				analogWrite(M2_SPEED, M_ALL_PWM);
				analogWrite(M3_SPEED, M_ALL_PWM);
				analogWrite(M4_SPEED, M_ALL_PWM);
			break;
		
			
		}//end Motor FSM
		
		//LCD_UPDATE(); //UPDATE THE LCD SCREEN
		OLED_UPDATE();
	}//end Serial Read
}//End Void loop

void OLED_INIT()
{
	oled.begin();
	oled.clearBuffer();
	oled.setCursor(0,0);
	oled.putString("Motor Controls");
	
}//end OLED_INIT

void OLED_UPDATE()
{
int adc_data = 0;
int thousands = 0;
int hundreds = 0;
int tens = 0;
int ones = 0;

//Motor 1
	adc_data = M1_PWM;
  //parse data
  ones = adc_data%10;
  adc_data = adc_data/10;
  tens = adc_data%10;
  adc_data = adc_data/10;
  hundreds = adc_data%10;
  adc_data = adc_data/10;
  thousands = adc_data%10;

  //convert data to ASCII
   thousands = thousands+48;
   hundreds = hundreds+48;
   tens = tens+48;
   ones = ones+48;

	oled.setCursor(0, 2);
	oled.putString("M1:");
    IOShieldOled.setCursor(4, 2);
    IOShieldOled.putChar(hundreds);
    IOShieldOled.setCursor(5, 2);
    IOShieldOled.putChar(tens);
    IOShieldOled.setCursor(6, 2);
    IOShieldOled.putChar(ones);
	
//Motor 2
	adc_data = M2_PWM;
  ones = adc_data%10;
  adc_data = adc_data/10;
  tens = adc_data%10;
  adc_data = adc_data/10;
  hundreds = adc_data%10;
  adc_data = adc_data/10;
  thousands = adc_data%10;

  //convert data to ASCII
   thousands = thousands+48;
   hundreds = hundreds+48;
   tens = tens+48;
   ones = ones+48;

	oled.setCursor(8, 2);
	oled.putString("M2:");
    IOShieldOled.setCursor(12, 2);
    IOShieldOled.putChar(hundreds);
    IOShieldOled.setCursor(13, 2);
    IOShieldOled.putChar(tens);
    IOShieldOled.setCursor(14, 2);
    IOShieldOled.putChar(ones);	
	


//Motor 3
adc_data = M3_PWM;
  //parse data
  ones = adc_data%10;
  adc_data = adc_data/10;
  tens = adc_data%10;
  adc_data = adc_data/10;
  hundreds = adc_data%10;
  adc_data = adc_data/10;
  thousands = adc_data%10;

  //convert data to ASCII
   thousands = thousands+48;
   hundreds = hundreds+48;
   tens = tens+48;
   ones = ones+48;


	oled.setCursor(0, 3);
	oled.putString("M3:");
    IOShieldOled.setCursor(4, 3);
    IOShieldOled.putChar(hundreds);
    IOShieldOled.setCursor(5, 3);
    IOShieldOled.putChar(tens);
    IOShieldOled.setCursor(6, 3);
    IOShieldOled.putChar(ones);

//Motor 4
adc_data = M4_PWM;
  //parse data
  ones = adc_data%10;
  adc_data = adc_data/10;
  tens = adc_data%10;
  adc_data = adc_data/10;
  hundreds = adc_data%10;
  adc_data = adc_data/10;
  thousands = adc_data%10;

  //convert data to ASCII
   thousands = thousands+48;
   hundreds = hundreds+48;
   tens = tens+48;
   ones = ones+48;


	oled.setCursor(8, 3);
	oled.putString("M4:");
    IOShieldOled.setCursor(12, 3);
    IOShieldOled.putChar(hundreds);
    IOShieldOled.setCursor(13, 3);
    IOShieldOled.putChar(tens);
    IOShieldOled.setCursor(14, 3);
    IOShieldOled.putChar(ones);
}//end OLED update

//Intialize the LCD Screen
void LCD_Init()
{

	Serial.write(254); // move cursor to beginning of first line
	Serial.write(128);
	Serial.write("                "); // clear display
	Serial.write("                ");
	Serial.write("    Dronenet    ");
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(192);
	Serial.write("Motor Controls");
	delay(1000);
	
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(128);
	Serial.write("                "); // clear display
	Serial.write("                ");
	Serial.write("Just Chillin");
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(192);
	Serial.write("Speed: JTC");
	
for (i=0; i<8; i++)
	{
		Serial.print(bitRead(data_read, i));
		digitalWrite(M_DIR[i], bitRead(data_read,i));
	}
	Serial.println();

}//end LCD_INIT


//Update the LCD values
void LCD_UPDATE()
{
//************* Motor 1********************//
	Serial.write(254);
	Serial.write(130);
	Serial.write("M1 ");
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(133);

	if(M_SPD[0] < 10)
		Serial.write("  ");
	else if(M_SPD[0] <100)
		Serial.write(" ");

	Serial.print(M_SPD[1]);
	
//************* Motor 2********************//
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(136);
	Serial.write(" M2 ");
	if(M_SPD[1] < 10)
		Serial.write("  ");
	else if(M_SPD[1] <100)
		Serial.write(" ");
		
	Serial.print(M_SPD[2]);

//************* Motor 3********************//
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(192);
	Serial.write("  M3 ");
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(197);

	if(M_SPD[2] < 10)
		Serial.write("  ");
	else if(M_SPD[2] <100)
		Serial.write(" ");
		
	Serial.print(M_SPD[2]);
	
//************* Motor 4********************//
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(200);
	Serial.write(" M4 ");
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(204);

	if(M_SPD[3] < 10)
		Serial.write("  ");
	else if(M_SPD[3] <100)
		Serial.write(" ");
		
	Serial.print(M_SPD[3]);

}//end LCD_UPDATE
