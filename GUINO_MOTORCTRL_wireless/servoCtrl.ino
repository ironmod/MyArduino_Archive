void servoCtrl()
{
  int pos=0;
  i=0;
  for (pos=50; pos<140; pos+=10)
  { 
    delay(scanRate);
    pan.write(pos);
   // range = rangeSensorAD.getRange();
//    range=range/2.54; //inches conversion
    gUpdateValue(&range);
//0 
    if(i==0)
    {
      r0=range;
      gUpdateValue(&r0);
      delay(10);
      if( (r0>(r0old-thresh)) && (r0<(r0old+thresh)) )
      {
        analogMeter1=0;

      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        gUpdateValue(&analogMeter1);
        delay(15);
      }
      r0old=r0;
      }
//1      
    else if(i==1)
    {
      r1=range;
      gUpdateValue(&r1);
      delay(10);
      if( (r1>(r1old-thresh)) && (r1<(r1old+thresh)) )
      {
        analogMeter1=1;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }

      r1old=r1;
      analogMeter2=r1old;
      gUpdateValue(&analogMeter2);
    }
//2
    else if (i==2)
    {
      r2=range;
      gUpdateValue(&r2);
      delay(10);
      if( (r2>(r2old-thresh)) && (r2<(r2old+thresh)) )
      {
        analogMeter1=2;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
       }
      r2old=r2;
    }
//3
    else if (i==3)
    {
      r3=range;
      gUpdateValue(&r3);
      delay(10);
      if( (r3>(r3old-thresh)) && (r3<(r3old+thresh)) )
      {
        analogMeter1=3;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }
      r3old=r3;
    }
//4
    else if (i==4)
    {
      r4=range;
      gUpdateValue(&r4);
      delay(10);
      if( (r4>(r4old-thresh)) && (r4<(r4old+thresh)) )
      {
        analogMeter1=4;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }
      r4old=r4;
    }
//5
    else if (i==5)
    {
      r5=range;
      gUpdateValue(&r5);
      delay(10);
      if( (r5>(r5old-thresh)) && (r5<(r5old+thresh)) )
      {
        analogMeter1=5;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }
      r5old=r5;
    }
//6
    else if (i==6)
    {
      r6=range;
      gUpdateValue(&r6);
      delay(10);
      if( (r6>(r6old-thresh)) && (r6<(r6old+thresh)) )
      {
        analogMeter1=6;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }
      r6old=r6;
    }
//7
    else if (i==7)
    {
      r7=range;
      gUpdateValue(&r7);
      delay(10);
      if( (r7>(r7old-thresh)) && (r7<(r7old+thresh)) )
      {
        analogMeter1=7;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }
      r7old=r7;
    }
//10
    else if (i==10)
    {
      r8=range;
      gUpdateValue(&r8);
      delay(10);
      if( (r8>(r8old-thresh)) && (r8<(r8old+thresh)) )
      {
        analogMeter1=8;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }
      r8old=r8;
    }
//9
    else if (i==9)
    {
      r9=range;
      gUpdateValue(&r9);
      delay(10);
      if( (r9>(r9old-thresh)) && (r9<(r9old+thresh)) )
      {
        analogMeter1=9;
        gUpdateValue(&analogMeter1);
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(3000);
        digitalWrite(10, LOW);
        delay(15);
      }
      r9old=r9;
    }
//    else if (i==10)
//      r10=range;
//    else if (i==11)
//      r11=range;
//    else if (i==12)
//      r12=range;
//    else if (i==13)
//      r13=range;
//    else if (i==14)
//      r14=range;
//    else if (i==15)
//      r15=range;
//    else if (i==16)
//      r16=range;
//    else if (i==17)
//    {
//       r17=range;
//    }
   gUpdateValue(&r0);
   gUpdateValue(&r1);
   gUpdateValue(&r2);
   gUpdateValue(&r3);
   gUpdateValue(&r4);
   gUpdateValue(&r5);
   gUpdateValue(&r6);
   gUpdateValue(&r7);
   gUpdateValue(&r8);
   gUpdateValue(&r9);
   gUpdateValue(&r10);
   gUpdateValue(&r11);
   gUpdateValue(&r12);
   gUpdateValue(&r13);
   gUpdateValue(&r14);
   gUpdateValue(&r15);
   gUpdateValue(&r16);
   gUpdateValue(&r17);

  i++;

  }
}
