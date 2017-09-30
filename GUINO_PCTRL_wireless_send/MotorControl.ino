void MotorControl()
{

  if (!reverse)
    {
      counter=1;
      mySerial.println("Y");
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
     
  
  speedCtrl=analogRead(A0);
  speedCtrl=map(speedCtrl, 0, 1023, 0, 255);
  if (speedOld != speedCtrl)
  {
    mySerial.println("S" + speedCtrl);
   // mySerial.println(speedCtrl);
    gUpdateValue(&speedCtrl);
  }
 else if ( (speedCtrl > (speedOld + thresh)) && (speedCtrl<(speedOld - thresh)) )
  {
    mySerial.println("S" + speedCtrl);
//    mySerial.println(speedCtrl);
    gUpdateValue(&speedCtrl);
  }
  delay(10);
  speedOld = speedCtrl;
  

} //end motorControl
