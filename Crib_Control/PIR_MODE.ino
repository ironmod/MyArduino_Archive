void PIR_MODE(){
//color scale to adjust the default color when the PIR is activated 
  int R_scale = 0;
  int G_scale = 0;
  int B_scale = 0;
  
 //digitalWrite(R2, LOW);
 //digitalWrite(G2, LOW);
// digitalWrite(B2, LOW);
//  
//  analogWrite(R2, R_scale);
//  analogWrite(G2, G_scale);
//  analogWrite(B2, B_scale);

  // set the brightness of pin 9:
  analogWrite(R2, brightness);    
  analogWrite(G2, brightness);
  analogWrite(B2, brightness);
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
     if (brightness==0 || brightness==255){
      fadeAmount= -fadeAmount;
    }
  // wait for 30 milliseconds to see the dimming effect    
  delay(100);      
}
