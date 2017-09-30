

#include <SoftwareSerial.h>
#include "math.h"
#include <genieArduino.h>

//********** Touchscreen Variables *************//
int reading_index = 0;
int indexer = 0;
int slider_array[] = {2, 3, 4, 5, 6, 7, 8};
  int slider2 = 0;
  int slider1 = 0;
/************************************************************************/
/*						Initial Setup Routine                           */
/************************************************************************/
void setup()
{
/************************* Initialize IO ********************************/	

	
/********************Initialize TouchScreen **********************************/	         
	genieBegin (GENIE_SERIAL, 115200);//Serial0
	genieAttachEventHandler(myGenieEventHandler);
	pinMode(4, OUTPUT);  				// 4D Display Reset Pin
	digitalWrite(4, 1);  				// Reset the Display via D4
	delay(100);
	digitalWrite(4, 0);				// unReset the Display via D4
	delay (2000); 					//let the display start up

/******************	Begin Authentication **********************************/	  
	genieWriteObject(GENIE_OBJ_FORM, 0x05, 1); //open the Security Screen
	genieWriteObject(GENIE_OBJ_SOUND, 0x00, 10);

//Start normal operations
	//genieWriteObject(GENIE_OBJ_SOUND, 0x00, 2);
	//delay(3000);
	genieWriteObject(GENIE_OBJ_FORM, 	0x00, 1);
	genieWriteObject(GENIE_OBJ_SOUND, 0x00, 6); //play sound on startup
}

void loop ()
{
	//genieDoEvents();
	genieReadObject(GENIE_OBJ_SLIDER, 0x01);
	genieWriteObject(GENIE_OBJ_COOL_GAUGE, 0x01, slider1); 
	
	genieReadObject(GENIE_OBJ_SLIDER, 0x02);
	genieWriteObject(GENIE_OBJ_COOL_GAUGE, 0x02, slider2);   
	
	genieReadObject(GENIE_OBJ_SLIDER, 0x03);
	genieReadObject(GENIE_OBJ_SLIDER, 0x04);
	genieReadObject(GENIE_OBJ_4DBUTTON, 0x00);
	delay(500);
}

/************************************************************************/
/*						4D LCD Event Handler			                */
/************************************************************************/

void myGenieEventHandler(void) 
{
  genieFrame Event;
  int slider_val = 0;   
  int slider_val1 = 0;
  int slider_val2 = 0;
  int BUTTON_STATE = 0;
  genieDequeueEvent(&Event);

  //Read from Slider0 for both a Reported Message from Display, and a Manual Read Object from loop code above
  //if (genieEventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_SLIDER, 2) ||
    //genieEventIs(&Event, GENIE_REPORT_OBJ,   GENIE_OBJ_SLIDER, 2)) 
if (genieEventIs(&Event, GENIE_REPORT_OBJ,   GENIE_OBJ_SLIDER, 1)) 
  {
    slider_val = genieGetEventData(&Event);  // Receive the event data from the Slider0
    genieWriteObject(GENIE_OBJ_COOL_GAUGE, 0x00, slider_val);     
	slider_array[2] = slider_val;
	//genieWriteObject(GENIE_OBJ_LED_DIGITS, 0x03, slider_val);

  }
  
else if (genieEventIs(&Event, GENIE_REPORT_OBJ,   GENIE_OBJ_SLIDER, 2)) 
  {
    slider_val = genieGetEventData(&Event);  // Receive the event data from the Slider0
    genieWriteObject(GENIE_OBJ_COOL_GAUGE, 0x01, slider_val);   
	slider_array[3] = slider_val;
  }
  
 else if (genieEventIs(&Event, GENIE_REPORT_OBJ,   GENIE_OBJ_SLIDER, 3)) 
  {
    slider_val = genieGetEventData(&Event);  // Receive the event data from the Slider0
    genieWriteObject(GENIE_OBJ_COOL_GAUGE, 0x02, slider_val);     
	slider_array[4] = slider_val;
  }
  
 else if (genieEventIs(&Event, GENIE_REPORT_OBJ,   GENIE_OBJ_SLIDER, 4)) 
  {
    slider_val = genieGetEventData(&Event);  // Receive the event data from the Slider0
    genieWriteObject(GENIE_OBJ_COOL_GAUGE, 0x03, slider_val);     
	slider_array[5] = slider_val;
  }
  
 else if (genieEventIs(&Event, GENIE_REPORT_OBJ,   GENIE_OBJ_4DBUTTON, 0)) 
  {
    BUTTON_STATE = genieGetEventData(&Event);  // Receive the event data from the Slider0
    if(BUTTON_STATE > 0)
    {    
    	genieWriteObject(GENIE_OBJ_METER, 0x00, 0x10);
    }
    else
    {      	
     	genieWriteObject(GENIE_OBJ_METER, 0x00, 0x00);
    }
  }
    
}//end event handler

