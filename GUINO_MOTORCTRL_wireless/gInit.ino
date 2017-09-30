// Set up The interface
void gInit()
{
//**************Analog Meters Column 1*************//
  gAddLabel("Analog Inputs A0 A1 A2",1);
  gAddSpacer(1); 
  gAddMovingGraph("A0",0,1023, &analogMeter0, 10);
  gAddRotarySlider(0,1023,"A0",&analogMeter0);
  gAddMovingGraph("A1",0,1023, &analogMeter1, 10);
  gAddRotarySlider(0,1023,"A1",&analogMeter1);
  gAddMovingGraph("A2",0,1023, &analogMeter2, 10);
  gAddRotarySlider(0,1023,"A2",&analogMeter2);
 // gAddColumn();
  
//*************Analog Meters Column 2************//
//  gAddLabel("Analog Inputs A3 A3 A5",1);
//  gAddSpacer(1);  
//  gAddMovingGraph("A3",0,1023, &analogMeter3, 10);
//  gAddRotarySlider(0,1023,"A3",&analogMeter3);
//  gAddMovingGraph("A4",0,1023, &analogMeter4, 10);
//  gAddRotarySlider(0,1023,"A4",&analogMeter4); 
//  gAddMovingGraph("A5 ",0,1023, &analogMeter5, 10);
//  gAddRotarySlider(0,1023,"A5 ",&analogMeter5);


//************PWM Sliders**************************//
// // gAddColumn();
//  gAddLabel("PWM Outputs",1);
//  gAddSpacer(1); 
//  gAddSlider(0,255,"Pin 6 PWM ",&pwm3);
//  gAddSlider(0,255,"Pin 9 PWM ",&pwm4);
//  gAddSlider(0,255,"Pin 10 PWM ",&pwm5);
//  gAddSlider(0,255,"Pin 11 PWM ",&pwm6); 
//  gAddSlider(0,255,"Pin 13 PWM",&pwm7);

  
//************Spare IO Buttons************************//
//  gAddSpacer(2);
//  gAddLabel("Digital IO Control Buttons",1);
//  gAddSpacer(1);
//  gAddToggle("Digital Output 1 (TX)", &button1); 
//  gAddToggle("Digital Output 2 (RX)", &button2); 
//  //gAddToggle("Digital Output 3 (PWM)", &button3); 
//  gAddToggle("Digital Output 5 (PWM)", &button5); 
//  gAddToggle("Digital Output 6", &button6); 
//  gAddToggle("Digital Output 7", &button7); 
//  gAddToggle("Digital Output 9 (PWM)", &button9); 
//  gAddToggle("Digital Output 10 (PWM)", &button10); 
//  gAddToggle("Digital Output 11 (PWM)", &button11); 
//  gAddToggle("Digital Output 12", &button12); 
//  gAddToggle("Digital Output 13 (PWM)", &button13); 
    
//
////**********  Turret Controller ***************************// 
//  gAddColumn();
//  gAddSpacer(1);
//  gAddLabel("Turret Control", 1);
//  gAddSlider(0,180,"Pin 3: PAN",&pwm1);
//  gAddSlider(50,180,"Pin 5: TILT ",&pwm2);
//  gAddToggle("Calibrate Turret", &calibrateTurret);
//  gAddToggle("D4: ARM TURRET", &button4); 
//  gAddToggle("D8: MISSLE LAUNCH", &button8); 
//  gAddSpacer(1);
//  gAddSlider(100, 1000, "Scan Rate(100-1000ms)", &scanRate);
//  gAddSlider(0, 8, "Target Range Threshold", &thresh);
//  
////************** Range Array Values *****************************//
//  gAddColumn();
//  gAddSpacer(1);
//  gAddLabel("Range Data", 1);
//  gAddMovingGraph("Range ",0,660, &range, 10);
//  gAddSlider(0,660,"Range to Target (cm) : ",&range);
//  gAddSlider(0, 660, "Range 0: ", &r0);
//  gAddSlider(0, 660, "Range 1: ", &r1);
//  gAddSlider(0, 660, "Range 2: ", &r2);
//  gAddSlider(0, 660, "Range 3: ", &r3);
//  gAddSlider(0, 660, "Range 4: ", &r4);
//  gAddSlider(0, 660, "Range 5: ", &r5);
//  gAddSlider(0, 660, "Range 6: ", &r6);
//  gAddSlider(0, 660, "Range 7: ", &r7);
//  gAddSlider(0, 660, "Range 8: ", &r8);
//  gAddSlider(0, 660, "Range 9: ", &r9);
////  gAddSlider(0, 660, "Range 10: ", &r10);
////  gAddSlider(0, 660, "Range 11: ", &r11);
////  gAddSlider(0, 660, "Range 12: ", &r12);
////  gAddSlider(0, 660, "Range 13: ", &r13);
////  gAddSlider(0, 660, "Range 14: ", &r14);
////  gAddSlider(0, 660, "Range 15: ", &r15);
////  gAddSlider(0, 660, "Range 16: ", &r16);
////  gAddSlider(0, 660, "Range 17: ", &r17);
//  gAddSpacer(1);

//************** Motor Controller ***********************//  
  gAddColumn();
  gAddSpacer(1);
  gAddLabel("Motor Controls", 1);
  gAddMovingGraph("Speed", 0, 255, &speedCtrl, 10);
  gAddSlider(0, 255, "Speed Control", &speedCtrl);
  gAddToggle("Forward", &forward);
  gAddToggle("Left", &left);
  gAddToggle("Right", &right);
  gAddToggle("Reverse", &reverse);
    
  
//***************Color Choser****************************//
  gAddColumn();
  gAddSpacer(1);
  gAddLabel("RGB Color Wheel", 1);
  gAddSpacer(1);
  
  rotaryRID = gAddRotarySlider(0,255,"R",&r);
  rotaryGID = gAddRotarySlider(0,255,"G",&g);
  rotaryBID = gAddRotarySlider(0,255,"B",&b);    
   
}
