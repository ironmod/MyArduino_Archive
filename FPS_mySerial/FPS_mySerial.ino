#include <SoftwareSerial.h>



byte highbyte = 0;
byte lowbyte = 0; 

word checksum = 0;

byte highcheck = 0;
byte lowcheck = 0;

byte response = 0;



word parameterin = 0;
word checksumReply = 0;

boolean communicationError = false;
boolean checksumCorrect = true; 
boolean ack = true;

byte lbyte = 0;
byte hbyte = 0;
byte checklbyte = 0;
byte checkhbyte = 0;

const int transmitDelay = 500;

SoftwareSerial mySerial(4, 5); // RX, TX
void setup(){
  mySerial.begin(9600);
  Serial.begin(9600); 
  /* begins serial communication at 9600 baud rate (default) Also, I'm using the 2nd serial port on my Mega, if you have an
  uno, you might want to use Serial instead. If you have a Leonardo, you can use Serial1 which is separate from the serial
  used to communicate over USB. The uno only uses only one set of TX and RX to communicate, the same one it uses for
  USB. */
}

void loop(){
scannerCommand(0x01, 0); //I have written a function for sending command packets. All you have to do is type in the command and the the parameter.
waitForReply(); //I wrote this function to output the response of the device. checksumCorrect tells you if the checkSum matches the data sent. If it doesn't, there was an error. The variable parameterin is the parameter that the fingerprint scanner has sent the arduino. The variable ack tells whether the the scanner has sent an acknowledgemnt. If it is false, there has been an error, and you must check parameterin to see which error code has been sent. The variable communicationError tells if the arduino has read any bytes that are out of place. This should be false. Have a look at the function at the bottom for more info.

//Now we have initialized the device by sending it the code to "open." You can write your own function to handle any of the responses I have detailed above.

scannerCommand(0x12, 1); //command turns on the LED in the sensor.
waitForReply(); //Again, you can do whatever you want with the variables here.
if(Serial.read()=='a')
{
  scannerCommand(0x20, 1);
 //that's the end of this demo. If it worked properly, the light on the device should turn on.

while( 1 == 1){} //This just ends the code without looping it.
}

//OK, now here are the functions I used.


void scannerCommand(byte com, int param){ //This is the function that sends data to the device
  valueToWORD(param);
  calcChecksum(com, highbyte, lowbyte);
  mySerial.write(0x55);
  mySerial.write(0xaa);
  mySerial.write(0x01);
  mySerial.write((byte)0);
  mySerial.write(lowbyte);
  mySerial.write(highbyte);
  mySerial.write((byte)0);
  mySerial.write((byte)0);
  mySerial.write(com);
  mySerial.write((byte)0);
  mySerial.write(lowcheck);
  mySerial.write(highcheck);
}

void waitForReply(){ //This is the function that receives data from the device.
  communicationError = false;
  while(mySerial.available() == 0){}
  delay(transmitDelay);
  if(mySerial.read() == 0x55){
  } else {
    communicationError = true;
  }

  if(mySerial.read() == 0xAA){
  } else {
    communicationError = true;
  }

  if(mySerial.read() == 0x01){
  } else {
    communicationError = true;
  }

  if(mySerial.read() == 0x00){
  } else {
    communicationError = true;
  }

  lbyte = mySerial.read();
  hbyte = mySerial.read();

  parameterin = word(hbyte, lbyte);

  mySerial.read();
  mySerial.read();

  response = mySerial.read();

  if(response == 0x30){
    ack = true;
  } else {
    ack = false;
  }
  mySerial.read();

  checklbyte = mySerial.read();
  checkhbyte = mySerial.read();

  checksumReply = word(checkhbyte, checklbyte);

  if(checksumReply == 256 + lbyte + hbyte + response){
    checksumCorrect = true;
  } else {
    checksumCorrect = false;
  } 
}

void calcChecksum(byte c, byte h, byte l){ //Also uses this function I have shown above
  checksum = 256 + c + h + l; //adds up all the bytes sent
  highcheck = highByte(checksum); //then turns this checksum which is a word into 2 bytes
  lowcheck = lowByte(checksum);
}

void valueToWORD(int v){ //turns the word you put into it (the paramter in the code above) to two bytes
  highbyte = highByte(v); //the high byte is the first byte in the word
  lowbyte = lowByte(v); //the low byte is the last byte in the word (there are only 2 in a word)
}
