void FADE_MODE() { 

  // set the brightness of pin 9:
  analogWrite(R2, brightness);    
  analogWrite(G2, brightness);
  analogWrite(B2, brightness);
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(100);                            
}

