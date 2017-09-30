int input_value=0;

void setup() {
  Serial.begin(9600);
  Serial.println("hello");
}
void loop (){
  while(1)
  {
    if(!Serial.available())
      continue;
    
     int input = Serial.read();
      if((input < '0')|| (input > '9')) //makes sure the arduino is only transfering
        {                                     //8 bits of numerical data '0'=0x30 '9'=0x38 in ASCII
          break;
        }
        else
        {
          input_value = input_value*10 + (input - '0'); //converts ASCII to readable integer
        }
        Serial.println(input_value);
  }
  input_value=0;
}

