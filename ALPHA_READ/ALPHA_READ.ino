
byte plain[] =
{
  // 0xf3, 0x44, 0x81, 0xec, 0x3c, 0xc6, 0x27, 0xba, 0xcd, 0x5d, 0xc3, 0xfb, 0x08, 0xf2, 0x73, 0xe6
  0x68, 0x61, 0x72, 0x64, 0x77, 0x61, 0x72, 0x65, 0x73, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;
int i =0;
int index = 0;
void setup () {
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop () 
{
  while (Serial.available())
  {
    int alpha = Serial.read();
    Serial.println(alpha, HEX);
    plain[i] = alpha;
    i++;
  }
  if (i==31){
    Serial.print("I = ");
    Serial.println(i);
    while(index<i){
      Serial.println(plain[index], HEX);
      index++;
    }
  //  i=0;
  }
    
}

