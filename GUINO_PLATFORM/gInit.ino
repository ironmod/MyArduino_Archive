// Set up The interface
void gInit()
{
//Analog Input Graphs
  gAddLabel("Analog Inputs A0 A1 A2",1);
  gAddSpacer(1); 
  gAddMovingGraph("A0",0,1023, &analogMeter0, 10);
  gAddRotarySlider(0,1023,"A0",&analogMeter0);
  gAddMovingGraph("A1",0,1023, &analogMeter1, 10);
  gAddRotarySlider(0,1023,"A1",&analogMeter1);
  gAddMovingGraph("A2",0,1023, &analogMeter2, 10);
  gAddRotarySlider(0,1023,"A2",&analogMeter2);
  gAddColumn();
  
  gAddLabel("Analog Inputs A3 A3 A5",1);
  gAddSpacer(1);  
  
  gAddMovingGraph("A3",0,1023, &analogMeter3, 10);
  gAddRotarySlider(0,1023,"A3",&analogMeter3);
  gAddMovingGraph("A4",0,1023, &analogMeter4, 10);
  gAddRotarySlider(0,1023,"A4",&analogMeter4); 
  gAddMovingGraph("A5 ",0,1023, &analogMeter5, 10);
  gAddRotarySlider(0,1023,"A5 ",&analogMeter5);

//Set PWM Output Graphs
  gAddColumn();
  gAddLabel("PWM Outputs",1);
  gAddSpacer(1); 
 

  gAddSlider(0,255,"Pin 6 PWM ",&pwm3);
  gAddSlider(0,255,"Pin 9 PWM ",&pwm4);
  gAddSlider(0,255,"Pin 10 PWM ",&pwm5);
  gAddSlider(0,255,"Pin 11 PWM ",&pwm6); 
  gAddSlider(0,255,"Pin 13 PWM",&pwm7);

  
//Set Buttons
  gAddSpacer(2);
  gAddLabel("Digital IO Control Buttons",1);
  gAddSpacer(1);
  gAddToggle("Digital Output 1 (TX)", &button1); 
  gAddToggle("Digital Output 2 (RX)", &button2); 
  gAddToggle("Digital Output 3 (PWM)", &button3); 

  gAddToggle("Digital Output 5 (PWM)", &button5); 
  gAddToggle("Digital Output 6", &button6); 
  gAddToggle("Digital Output 7", &button7); 
 
  gAddToggle("Digital Output 9 (PWM)", &button9); 
  gAddToggle("Digital Output 10 (PWM)", &button10); 
  gAddToggle("Digital Output 11 (PWM)", &button11); 
  gAddToggle("Digital Output 12", &button12); 
  gAddToggle("Digital Output 13 (PWM)", &button13); 
    

//**********  Turret Controller ***************************// 
  gAddColumn();
  gAddSpacer(1);
  gAddLabel("Turret Control", 1);
  gAddMovingGraph("Range ",0,120, &range, 10);
  gAddSlider(0,160,"Range to Target (cm) : ",&range);
  gAddSlider(0,180,"Pin 3: PAN",&pwm1);
  gAddSlider(50,180,"Pin 5: TILT ",&pwm2);
  gAddToggle("D4: Arm Turret", &button4); 
  gAddToggle("D8: MISSLE LAUNCH", &button8); 
  gAddSpacer(1);
  
//***************Color Choser****************************//
  gAddSpacer(1);
  gAddLabel("RGB Color Wheel", 1);
  gAddSpacer(1);
  
  rotaryRID = gAddRotarySlider(0,255,"R",&r);
  rotaryGID = gAddRotarySlider(0,255,"G",&g);
  rotaryBID = gAddRotarySlider(0,255,"B",&b);    
   
}
