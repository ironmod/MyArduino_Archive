#define isdigit(X) (((X) >= '0') && ((X) <= '9')

int read_int()
{
  static byte c;
  static int i;

  i = 0;
  while (1)
  {
    while (!Serial.available())
    {;}
 
    c = Serial.read();
    Serial.print(c, BYTE);
  
    if (c == '\r')
    {
      return i;
    }
    if (isdigit(c))
    {
      i = i * 10 + c - '0';
    }
    else
    {
      Serial.print("\r\nERROR: \"");
      Serial.print(c, BYTE);
      Serial.print("\" is not a digit\r\n");
      return -1;
    }
  }
}
