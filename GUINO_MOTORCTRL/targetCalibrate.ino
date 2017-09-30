void targetCalibrate()
{
  int pos=0;
  i=0;
  for (pos=50; pos<140; pos+=10)
  { 
    delay(scanRate);
    pan.write(pos);
    range = rangeSensorAD.getRange();
    //range=range/2.54;
    gUpdateValue(&range);
//0 
    if(i==0)
    {
      r0=range;
      gUpdateValue(&r0);
      r0old=r0;
      }
//1      
    else if(i==1)
    {
      r1=range;
      gUpdateValue(&r1);
      r1old=r1;
    }
//2
    else if (i==2)
    {
      r2=range;
      gUpdateValue(&r2);
      r2old=r2;
    }
//3
    else if (i==3)
    {
      r3=range;
      gUpdateValue(&r3);
      r3old=r3;
    }
//4
    else if (i==4)
    {
      r4=range;
      gUpdateValue(&r4);
      r4old=r4;
    }
//5
    else if (i==5)
    {
      r5=range;
      r5old=r5;
    }
//6
    else if (i==6)
    {
      r6=range;
      gUpdateValue(&r6);
      r6old=r6;
    }
//7
    else if (i==7)
    {
      r7=range;
      r7old=r7;
    }
//8
    else if (i==8)
    {
      r8=range;
      gUpdateValue(&r8);
      r8old=r8;
    }
//9
    else if (i==9)
    {
      r9=range;
      gUpdateValue(&r9);
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
