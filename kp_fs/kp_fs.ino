/*
		:: Platform Security Authentication HSM ::
				:: Fingerprint Scanner ::
				:: PIN Authentication  ::
							,---.
                          /    |
                         /     |
     Gandalf            /      |
                       /       |
                  ___,'        |
                <  -'          :
                 `-.__..--'``-,_\_
                    |o/ <o>` :,.)_`>
                    :/ `     ||/)
                    (_.).__,-` |\
                    /( `.``   `| :
                    \'`-.)  `  ; ;
                    | `       /-<
                    |     `  /   `.
    ,-_-..____     /|  `    :__..-'\
   /,'-.__\\  ``-./ :`      ;       \
   `\ `\  `\\  \ :  (   `  /  ,   `. \
     \` \   \\   |  | `   :  :     .\ \
      \ `\_  ))  :  ;     |  |      ): :
     (`-.-'\ ||  |\ \   ` ;  ;       | |
      \-_   `;;._   ( `  /  /_       | |
       `-.-.// ,'`-._\__/_,'         ; |
          \:: :     /     `     ,   /  |
           || |    (        ,' /   /   |
           ||                ,'   / SSt|

				Dare you Pass?
*/


#include <Keypad.h>
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
#include "Math.h"


const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
char master_pw[] = "1234";	//Stores Master Password

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {10, 6, 7, 8}; //connect to the row pinouts of the keypad
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {2, 3, 9}; //connect to the column pinouts of the keypad
// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
FPS_GT511C3 fps(4, 5);		//finger print scanner UART pins(software serial)
int verified = false;		//becomes TRUE if the PIN is verified
int fsm_state 		= 0;	//FSM state for determining if PIN is valid
char key; 					//key read from keypad
int PIN_VERIFIED 	= A0;	//set this pin HIGH when PIN is verified (used as backdoors)
int FPS_VERIFIED 	= A1;	//set this pin HIGH when FPS is verified (used as backdoors)
int FPS_FAILED		= A2;	//goes high if FPS fails after 3 attempts
int PIN_FAILED		= A3;	//goes HIGH if PIN fails after 3 attempts
int fps_fail_cnt 	= 0;	//count how many times FPS failed
int pin_failed_cnt 	= 0;	//count how many times PIN failed


/************************************************************************/
/*						Initial Setup Routine                           */
/************************************************************************/
void setup()
{

  Serial.begin(9600);
  Serial.println("DRONET HSM: PIN && FPS VERIFICATION");
  pinMode(PIN_VERIFIED, OUTPUT);
  pinMode(FPS_VERIFIED, OUTPUT);
  pinMode(FPS_FAILED, 	OUTPUT);
  pinMode(PIN_FAILED,	OUTPUT);
  digitalWrite(PIN_VERIFIED, LOW);
  digitalWrite(FPS_VERIFIED, LOW);
  digitalWrite(FPS_FAILED,	 LOW);
  digitalWrite(PIN_FAILED, 	 LOW);
  
  delay(100);
  fps.Open();
  fps.SetLED(true);
  delay(500);
  fps.SetLED(false);
  delay(500);
  fps.SetLED(true);
  delay(500);
  fps.SetLED(false);
  delay(500);
  fps.SetLED(true);
  delay(500);
  fps.SetLED(false);
  delay(500);
  fps.SetLED(true);
  delay(500);
  fps.SetLED(false);
}


/************************************************************************/
/*						Infinite Loop/Run Mode                          */
/************************************************************************/
void loop()
{
//Password FSM. Turns on FPS when corrected password is entered
	switch(fsm_state)
	{
		case 0:
			Serial.println("FSM: 0");
			key = kpd.getKey();			//read keypad
			if(key && (key == master_pw[0]))		//if key is valid and key == password[1]
				fsm_state = 1;
				
			//alert that the PIN has failed authentication 3 times
			if(pin_failed_cnt == 3)
			{
				digitalWrite(PIN_FAILED, HIGH);
				Serial.println("PIN AUTHENTICATION FAILED");
				while(1)
				{}; //halt processor until resset
			}
			break;
			
		case 1:
			Serial.println("FSM: 1 ");
			key = kpd.getKey();
			if(key && (key == master_pw[1]))
				fsm_state = 2;
			else if (key)
			{
				fsm_state = 0;
				pin_failed_cnt++;
			}
			break;
			
		case 2:
			Serial.println("FSM: 2");
			key = kpd.getKey();
			if(key && (key == master_pw[2]))
				fsm_state = 3;
			else if (key)
			{
				fsm_state = 0;
				pin_failed_cnt++;
			}
			break;
			
		case 3:
			Serial.println("FSM: 3");
			key = kpd.getKey();
			if(key && (key == master_pw[3]))
				fsm_state = 4;
			else if (key)
			{
				fsm_state = 0;
				pin_failed_cnt++;
			}
			break;
			
		case 4:
			Serial.println("Key Verified");
			verified = true;
			fsm_state = 5;
			fps.SetLED(true);
			digitalWrite(PIN_VERIFIED, HIGH);	//tell the PIC32 pin is complete
			pin_failed_cnt==0;
			break;

	} //end FSM


// Identify fingerprint test
	if (fps.IsPressFinger() && verified==true)
	{
		fps.CaptureFinger(false);
		int id = fps.Identify1_N();
		if (id <200)
		{
			Serial.print("Verified ID:");
			fps.SetLED(false);
			Serial.println(id);
			digitalWrite(FPS_VERIFIED, HIGH); //tell PIC32 FPS is verified
		}
		else
		{
			Serial.println("Finger not found");\
			
			//update FPS_FAILED counter
			fps_fail_cnt++;
			if(fps_fail_cnt == 3)
			{
				digitalWrite(FPS_FAILED, HIGH);
				while(1) //halt processor until reset 
				{}
			}
				
			//flash FPS LED
			fps.SetLED(false);
			delay(50);
			fps.SetLED(true);
			delay(50);
			fps.SetLED(false);
			delay(50);
			fps.SetLED(true);
			delay(50);
		}
	}

	delay(100);
}
