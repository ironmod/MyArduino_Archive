/*----------------------------------------------------------------------*/
/*									DRONENET  							*/
/*						Platform Motor Controller Firmware				*/
/*						University of Central Florida					*/
/*								Brandon Frazer							*/
/*----------------------------------------------------------------------*/

/*								REV3: 2/8/2014							*/
/*						Integrated Serial Debugging Menu				*/
/*				Enabled Each Motor to be addressed by a Byte			*/

#include "math.h"


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
//Motor Speed Variables
int M1_SPEED 	= 3;
int M2_SPEED	= 10;
int M3_SPEED 	= 5;
int M4_SPEED	= 11;
int M_ALL_PWM 	= 0;

//Array holding all the Physical Pin #'s for the Motor Driver
int M_DIR[] = { IN1, IN2, IN3, IN4, IN5, IN6, IN7, IN8 };
//Array for the Speed Variables at the Motors (PWM)
int M_SPD[] = { 0, 0, 0, 0 };
//Array Holding all the Physical Pins to write the PWM Values too
int M_PWM[] = {M1_SPEED, M2_SPEED, M3_SPEED, M4_SPEED};
//data_read from the XBEE
int data_read = B00000000;
int MOTOR_DIR = B00000000;
int i = 0; //for loop counter
//statements for debugging and updating
boolean DEBUG = true;
boolean UPDATE_COUNTER = true;
boolean clear_screen = false;

/************************************************************************/
/*						Initial Setup Routine                           */
/************************************************************************/
void setup ()
{
	Serial.begin(9600);
	if(!DEBUG)
		LCD_Init();
	//
	else if(DEBUG)
	{
		DEBUG_INIT();
	}
		
//Set all pins as OUTPUTS
for (i=0; i<8; i++)
	{
		pinMode(M_DIR[i], OUTPUT);
	}
//Clear the PWM Values on startup
for (i=0; i<8; i++)
	{
		digitalWrite(M_DIR[i], bitRead(data_read,i));
	}
}//end setup

/************************************************************************/
/*						Infinite Loop/Run Mode                          */
/************************************************************************/
void loop ()
{
	while(Serial.available())
	{
		data_read = Serial.read();
		switch(data_read)
		{
		//Assign Motor Direction
			case 'D':		
				MOTOR_DIR = Serial.parseInt();	
				for (i=7; i>=0; i--)
				{
					digitalWrite(M_DIR[i], bitRead(MOTOR_DIR, i));
				}
			break;
		
		//Assign Motor Speeds Individually 
			case '1':
				M_SPD[0] = Serial.parseInt();
				M_SPD[0] = constrain(M_SPD[0], 0 ,255);
                //Serial.println(M_SPD[0]);
				analogWrite(M1_SPEED, M_SPD[0]);
			break;
			
			case '2':
				M_SPD[1] = Serial.parseInt();
				M_SPD[1] = constrain(M_SPD[1], 0 ,255);
				analogWrite(M2_SPEED, M_SPD[1]);
			break;
			
			case '3':
				M_SPD[2] = Serial.parseInt();
				M_SPD[2] = constrain(M_SPD[2], 0 ,255);
				analogWrite(M3_SPEED, M_SPD[2]);
			break;
			
			case '4':
				M_SPD[3] = Serial.parseInt();
				M_SPD[3] = constrain(M_SPD[3], 0 ,255);
				analogWrite(M4_SPEED, M_SPD[3]);
			break;
		
		//Use the same speed for all motors
			case '5':
				M_ALL_PWM = Serial.parseInt();
				M_ALL_PWM = constrain(M_ALL_PWM, 0 ,255);
				for(i=0; i<4; i++)
				{
					M_SPD[i] = M_ALL_PWM;
					analogWrite(M_SPD[i], M_ALL_PWM);
				}
			break;
					
		}//end Motor FSM
		
		//Update the LCD Screen when NOT in debug 
		//update_counter helps with the refresh rate(1 time vs 3)
		if(!DEBUG && UPDATE_COUNTER)
		{
			UPDATE_COUNTER = false;
			LCD_UPDATE(); 
		}
		
		//update debug serial monitor
		else if (DEBUG && UPDATE_COUNTER)
		{	
			UPDATE_COUNTER = false;
			DEBUG_SERIAL();
		}
			
	}//end Serial Read
	
	//Reset the Update Counter  
	UPDATE_COUNTER = true;
}//End Void loop



/************************************************************************/
/*			Initialize Serial "DEBUG" Monitor Update                   */
/************************************************************************/
void DEBUG_INIT()
{
Serial.println(" /*********************************/ ");
Serial.println(" *           DRONENET             *  ");
Serial.println(" *     The Platform Of Peace	  *  ");
Serial.println(" *     Parameters and Settings    *  ");
Serial.println(" /*********************************/ ");
}//end DEBUG_INIT

/************************************************************************/
/*						Serial "DEBUG" Monitor Update                   */
/************************************************************************/
void DEBUG_SERIAL()
{
Serial.println(" /*********************************/ ");
Serial.println(" *           Parameters           *  ");
Serial.println(" /*********************************/ ");
Serial.print("Motor Direction: ");
for(i = 7; i!=0; i--)
{
	Serial.print(bitRead(MOTOR_DIR, i));
}
Serial.println();

//Print the Motor Speed Array
for (i=0; i!=4; i++)
{
	Serial.print("M");
	Serial.print(i);
	Serial.print(" Speed: ");
	Serial.println(M_SPD[i]);
}
Serial.println();

}//END DEBUG_SERIAL

/************************************************************************/
/*						Initialize the LCD Screen                      */
/************************************************************************/
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
	

	//Serial.println();

}//end LCD_INIT

/************************************************************************/
/*						Update the LCD Screen                           */
/************************************************************************/
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

	Serial.print(M_SPD[0]);
	
//************* Motor 2********************//
	Serial.write(254); // move cursor to beginning of first line
	Serial.write(136);
	Serial.write(" M2 ");
	if(M_SPD[1] < 10)
		Serial.write("  ");
	else if(M_SPD[1] <100)
		Serial.write(" ");
		
	Serial.print(M_SPD[1]);

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

/************************************************************************/
/*						Update the PWM Values                           */
/************************************************************************/
void PWM_UPDATE()
{
	for(i=0; i<4; i++)
	{
		analogWrite(M_PWM[i], M_SPD[i]);
	}

}//END PWM UPDATE

