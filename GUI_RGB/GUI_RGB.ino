// Dummy example variables
int amplitude = 20;
int width = 0;
int graphValue = 0;
int potMeter0 = 0;
int potMeter2 = 0;
int potMeter1 = 0;
float angle = 0;

int r = 0;
int g = 0;
int b = 0;
int rotaryRID,rotaryGID,rotaryBID;

void setup(){
  gBegin(34236); 
}

void loop(){
  // **** Main update call for the guino
  guino_update();

  // Read analog
   potMeter0 = analogRead(0);
   potMeter1 = analogRead(1);
   potMeter2 = analogRead(2);

   //Adjust RGB Values based off POT Values
   r = map(potMeter0, 0,1023, 0, 255);
   g = map(potMeter1, 0,1023, 0, 255);
   b = map(potMeter2, 0,1023, 0, 255);
   
  // Update Analog values
  gUpdateValue(&potMeter0);
  gUpdateValue(&potMeter1);
  gUpdateValue(&potMeter2);
  gUpdateValue(&r);
  gUpdateValue(&g);
  gUpdateValue(&b);
  
  //Write the new RGB Values
  gSetColor(r, g, b);  
}

// This is where you setup your interface 
void gInit()
{
  gAddLabel("Analog Inputs",2);
  gAddSpacer(1); 
 
  //Analog Input Graphs
  gAddMovingGraph("POT0",0,1023, &potMeter0, 20);
  gAddSlider(0,1023,"POT0",&potMeter0);
  
  gAddMovingGraph("POT1",0,1023, &potMeter1, 20);
  gAddSlider(0,1023,"POT1",&potMeter1);
  
  gAddMovingGraph("POT2",0,1023, &potMeter2, 20);
  gAddSlider(0,1023,"POT2",&potMeter2);
 
  gAddColumn();
  gAddColumn();
  gAddColumn();
  gAddLabel("RGB Color Wheel", 2);
   gAddSpacer(1);

 //Rotary RGB Graphs
  rotaryRID = gAddRotarySlider(0,255,"R",&r);
  rotaryGID = gAddRotarySlider(0,255,"G",&g);
  rotaryBID = gAddRotarySlider(0,255,"B",&b);
  // Add more stuff here.
  gSetColor(r,g,b); // Set the color of the gui interface. 
}

// Method called everytime a button has been pressed in the interface.
void gButtonPressed(int id)
{

}

void gItemUpdated(int id)
{

}






