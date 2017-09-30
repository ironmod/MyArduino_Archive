// Select button is triggered when joystick is pressed
#include "math.h"


const byte MOVE_RVS = B10101010;
const byte MOVE_FWD = B01010101;
const byte MOVE_LFT = B01011010;
const byte MOVE_RGT = B10100101;
const byte STRF_LFT = B01101001;
const byte STRF_RGT = B10010110;
const byte NEUTRAL  = B00000000;

const byte SELECT = 2;

const byte RIGHT = 3;
const byte UP = 4;
const byte DOWN = 5;
const byte LEFT = 6;

int joystick_y = 0;
int joystick_x = 0;
int speed_ctrl = 0;
int speed_ctrl_old = 0;
int counter = 0;
int js_x_center = 497;
int js_y_center = 507;
void setup () 
{
  Serial.begin(9600);
  //Serial.print("Hello World");
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(SELECT, INPUT_PULLUP);
  
}

void loop () {
//	joystick_y=analogRead(A1);
	joystick_x=analogRead(A1);

 if( digitalRead(RIGHT)==LOW && counter!=20)
//  if( (joystick_x > js_x_center) && counter != 20)
  {
    counter++;  
     Serial.println("R");
     //Serial.print(MOVE_RGT);
  }
  
  else if(digitalRead(LEFT)==LOW && counter!=20)
  //else if ((joystick_x < js_x_center) && counter != 20)
  {
    counter++;
	Serial.println("L");
	//Serial.println(MOVE_LFT);
  }
  
 else if(digitalRead(UP)==LOW && counter!=20)
//else if (joystick_y > js_y_center && counter != 20)
  {
    counter++;
    Serial.println("F");
	//Serial.println(MOVE_FWD);
  }

  else if(digitalRead(DOWN)==LOW && counter!=20)
//else if((joystick_y < js_y_center) && counter !=20)
  {
      counter++;
      Serial.println("B");
	  //Serial.println(MOVE_RVS);
  }
  
  else if(digitalRead(DOWN) && digitalRead(UP) && digitalRead(LEFT) && digitalRead(RIGHT) && counter!=0)
  {
    counter =0;
	while(counter != 5)
	{
		Serial.println("N");
		counter++;
	}
	counter = 0;
	//Serial.println(NEUTRAL);
  }  
  //if(digitalRead(SELECT)==LOW)
    //Serial.println("Select");
	//if((joystick_y > js_y_center) || (joystick_x > js_x_center))
      if(joystick_x > js_x_center)
	{
           /* if(joystick_y > js_y_center)
            {
		speed_ctrl = map(joystick_y, js_y_center, 1023, 0, 255);
            }
            */
            //else if(joystick_x > js_x_center)
            //{
              speed_ctrl = map(joystick_x, js_x_center, 1023, 0, 255);
            //}
		if(speed_ctrl != speed_ctrl_old)
		{
			Serial.print("S");
			Serial.print("5");
			Serial.println(speed_ctrl);
		}
		speed_ctrl_old = speed_ctrl;
	}

/*	else if((joystick_y < js_y_center) || (joystick_x < js_x_center))
	{
            if(joystick_y < js_y_center)
            {
		speed_ctrl = map(joystick_y, 0, js_y_center,  255, 0);
            }
            else if(joystick_x < js_x_center)
            {
              speed_ctrl = map(joystick_x, js_x_center, 0, 255, 0);
            }
	  if(speed_ctrl != speed_ctrl_old)
		{
			Serial.print("S");
			Serial.print("5");
			Serial.println(speed_ctrl);
		}
		speed_ctrl_old = speed_ctrl;
	}
  */	
  delay(20);
}

