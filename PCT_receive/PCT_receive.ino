/*
											Platform Controls Receiver 
											::	Turret Controls	::
											::	Motor Controls	::
                                                     _..----.._                                   
                                                    ]_.--._____[                                  
                                                  ___|'--'__..|--._                               
                              __               """    ;            :                              
                            ()_ """"---...__.'""!":  /    ___       :                             
                               """---...__\]..__] | /    [ 0 ]      :                             
                                          """!--./ /      """        :                            
                                   __  ...._____;""'.__________..--..:_                           
                                  /  !"''''''!''''''''''|''''/' ' ' ' \"--..__  __..              
                                 /  /.--.    |          |  .'          \' ' '.""--.{'.            
             _...__            >=7 //.-.:    |          |.'             \ ._.__  ' '""'.          
          .-' /    """"----..../ "">==7-.....:______    |                \| |  "";.;-"> \         
          """";           __.."   .--"/"""""----...."""""----.....H_______\_!....'----""""]       
        _..---|._ __..--""       _!.-=_.            """""""""""""""                   ;"""        
       /   .-";-.'--...___     ." .-""; ';""-""-...^..__...-v.^___,  ,__v.__..--^"--""-v.^v,      
      ;   ;   |'.         """-/ ./;  ;   ;\P.        ;   ;        """"____;  ;.--""""// '""<,     
      ;   ;   | 1            ;  ;  '.: .'  ;<   ___.-'._.'------""""""____'..'.--""";;'  o ';     
      '.   \__:/__           ;  ;--""()_   ;'  /___ .-" ____---""""""" __.._ __._   '>.,  ,/;     
        \   \    /"""<--...__;  '_.-'/; ""; ;.'.'  "-..'    "-.      /"/    `__. '.   "---";      
         '.  'v ; ;     ;;    \  \ .'  \ ; ////    _.-" "-._   ;    : ;   .-'__ '. ;   .^".'      
           '.  '; '.   .'/     '. `-.__.' /;;;   .o__.---.__o. ;    : ;   '"";;""' ;v^" .^        
             '-. '-.___.'<__v.^,v'.  '-.-' ;|:   '    :      ` ;v^v^'.'.    .;'.__/_..-'          
                '-...__.___...---""'-.   '-'.;\     'WW\     .'_____..>."^"-""""""""    fsc       
                                      '--..__ '"._..'  '"-;;"""                                   
                                             """---'""""""      
*/
#include "Servo.h"
#include "math.h"
/************************************************************************/
/*						Serial Tag DataBase								*/
/************************************************************************/
/*				Pxxx: Pan Servo PWM Output (0-255)						*
*				A	: Launch Missiles									*
*				Txxx: Tilt Servo PWM Output (50-180)					*
*				Sxxx: Motor Speed Control (1-255)						*
*				F	: Move Forward										*
*				B	: Reverse											*
*				L	: Move Left											*
*				R	: Move Right										*
*				D	: Spare												*
*				Q	: Spare												*
*				Y:	: Spare												*
*				I:	: Spare												*
************************************************************************/

/*******************  Initialize Global Variables ********************/
String serialString;	//Not used right now.
Servo pan;				//Pan Servo for Turret
Servo tilt;				//Tilt Servo for Turret
int data =0;			//Serial Data Read in
int val=0;				//Serial Integer value
int flag =0;			//Serial Flag
int pwm_left = 10;		//ENA
int pwm_right = 11;		//ENB
int dir1_left = 7;		//IN1
int dir2_left = 9;		//IN2
int dir1_right = 12;	//IN3
int dir2_right = 13;	//IN4
int turret_fire = 8;	//MOSFET for Turret
int speedVal = 0;

/************************************************************************/
/*						Initial Setup Routine                           */
/************************************************************************/

void setup()
{
	Serial.begin(38400);
	Serial.print("Hello");
//Set pin directions	
	pinMode(dir1_left, OUTPUT);
	pinMode(dir2_left, OUTPUT);
	pinMode(dir1_right, OUTPUT);
	pinMode(dir2_right, OUTPUT);
	pinMode(pwm_right, OUTPUT);
	pinMode(pwm_left, OUTPUT);
	pinMode(turret_fire, OUTPUT);
//Shut off turret for safe measure. 
//attach servos 
	digitalWrite(turret_fire, LOW);
	pan.attach(3);
	tilt.attach(5);
}

/************************************************************************/
/*						Infinite Loop/Run Mode                          */
/************************************************************************/
void loop()
{
	//Serial Data Parser 
	while(Serial.available())
	{
		flag = Serial.read();
		
		//Call Turret Control Function
			turretControl();
		
		//Call Motor Control Function
			motorControl();
			
	}//end Serial Read While

	delay(20);
}//end void loop

/************************************************************************/
/*					Turret Movement and Missile Launch Controls         */
/************************************************************************/
void turretControl()
{
//Pan Servo Controls
	if (flag == 'P')				//check Tag
	{
		data = Serial.parseInt();	//parse the remainder as an Integer
		if(data != 0)
		{
			val = constrain(data, 0, 255); //just for safe measure 
			pan.write(val);
			Serial.println(val);
		}
	}
	
//Tilt Servo Controls
	else if (flag == 'T')
	{
		data = Serial.parseInt();
		if(data != 0)
		{
			val = constrain(data, 0, 255);
			tilt.write(val);
			Serial.println(val);
		}
	}
	
//Turret Fire
	else if (flag=='A')
	{
		digitalWrite(turret_fire, HIGH);
	}
	else if (flag=='Q')
		digitalWrite(turret_fire, LOW);
	
}//end Turret Controls

/************************************************************************/
/*					Motor Controls for Speed and Direction				*/
/************************************************************************/
void motorControl()
{
	
	//Motor Speed Controls
	if(flag=='S')
	{
		data = Serial.parseInt();
		if(data!=0)
		{
			speedVal = val;
			val = constrain(data, 0, 255);
			analogWrite(pwm_left, val);
			analogWrite(pwm_right, val);
		}
	}
	
	//Motor Direction Controls
	else if (flag=='B')
	{
		digitalWrite(dir1_left, HIGH);
		digitalWrite(dir2_left, LOW);
		digitalWrite(dir1_right, HIGH);
		digitalWrite(dir2_right, LOW);
	}
	
	else if(flag=='F')
	{
		digitalWrite(dir1_left, LOW);
		digitalWrite(dir2_left, HIGH);
		digitalWrite(dir1_right, LOW);
		digitalWrite(dir2_right, HIGH);
	}
	
	else if(flag=='L')
	{
		digitalWrite(dir1_left, LOW);
		digitalWrite(dir2_left, HIGH);
		digitalWrite(dir1_right, HIGH);
		digitalWrite(dir2_right, LOW);
	}
	
	else if(flag=='R')
	{
		digitalWrite(dir1_left, HIGH);
		digitalWrite(dir2_left, LOW);
		digitalWrite(dir1_right, LOW);
		digitalWrite(dir2_right, HIGH);
	}
	
	else if((flag=='N') || (speedVal < 10))//shut all motors off
	{
		digitalWrite(dir1_left, LOW);
		digitalWrite(dir2_left, LOW);
		digitalWrite(dir1_right, LOW);
		digitalWrite(dir2_right, LOW);
	}	
	
}//end motor control

