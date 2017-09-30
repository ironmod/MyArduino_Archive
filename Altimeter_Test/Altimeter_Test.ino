void setup()
{
  Serial.begin(9600);
  Serial.println("Yeah Buddy");
}

long Serial_atol()
{
  char ch = 0;
  long value = 0L;
  while(1)
  {
    if(!Serial.available())
      continue;
      
      ch = Serial.read();
      if((ch < '0')|| (ch > '9')) 
        {
          break;
        }
        else
        {
          value = value*10 + (ch - '0');
        }
  }
  return value;
}

void loop ()
{
  long altitude = Serial_atol();
  if(altitude!=0)
    {
      Serial.print("Altitude: ");
      Serial.println(altitude);
    }
}
