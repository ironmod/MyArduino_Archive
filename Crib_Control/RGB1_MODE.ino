void RGB1_MODE () {


   analogMeter0 = analogRead(0);
   analogMeter1 = analogRead(1);
   analogMeter2 = analogRead(2);
   analogMeter3 = analogRead(3);
   analogMeter4 = analogRead(4);
  
  //PWM Set to adjust off Analog/Potentiometer values
  pwm1 = map(analogMeter0, 0,1023, 0, 255);
   analogWrite(3, pwm1);
  pwm2 = map(analogMeter1, 0,1023, 0, 255);
   analogWrite(5, pwm2);
  pwm3 = map(analogMeter2, 0,1023, 0, 255);
    analogWrite(6, pwm3);
  pwm4 = map(analogMeter3, 0,1023, 0, 255);
   analogWrite(10, pwm4);    
  pwm5 = map(analogMeter4, 0,1023, 0, 255);
    analogWrite(9, pwm5);
  pwm6 = map(analogMeter5, 0,1023, 0, 255);
}
