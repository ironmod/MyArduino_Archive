void MotorControl()
{

  if (!reverse)
    {
      counter=1;
      mySerial.println("B");
    }
    
  else if(!forward)
    {
      counter=1;
      mySerial.println("F");
    } 
    
  else if(!left)
      {
        counter=1;
       mySerial.println("L");
      }
    
  else if(!right)
     {
       counter=1;
       mySerial.println("R");
     }
     
  
  speedCtrl=analogRead(A2);
  speedCtrl=map(speedCtrl, 0, 1023, 0, 255);
  gUpdateValue(&speedCtrl);


} //end motorControl
