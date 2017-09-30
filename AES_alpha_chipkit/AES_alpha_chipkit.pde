/*
Encryption Key Grabber (E.K.G.) 
Written by Brandon Frazer 
University of Central Florida
EEE4492: Hardware Security and Trusted Circuit Design 
Lab 1: Hardware Trojan Design in AES Crypto-System
Code Description:
  --Reads in a string of ciphered text from a BASYS2 running the ALPHA code
  --Decrypts the ciphered text but performing the XOR and AND ops to break the master key
  --Displays the new key as well as the information read in
  --Displays the orginal Plaintext on the IOShield OLED and on the Serial Monitor
  -- Using the on-board buttons on the uno32, it will take control of the FPGA and perform all the user functions
  --This was designed to be a one-shot system. So you will need to reset the MCU after it decrypts 
*/

#include <AES.h>
#include <IOShieldOled.h>

AES aes ;  
int i = -1;                //index_count counter for the incoming ciphered text. Start at -1 because the first 8 bits are the switch config
int index_count = 0;              
byte dynamic_key = 0x00;   //dynamic key to hold the switch pattern

//master key before any XOR or AND ops
byte key[16] = 
{
  0xFB, 0x79, 0x15, 0xBD, 0xF1, 0xE5, 0xC8, 0xB8, 0x4B, 0xB7, 0x18, 0xDD, 0x34, 0xD7, 0x33, 0xA5,
} ;
//malloc for the plain text after decryption
byte plain[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;
//Initilization vector (required for using this AES library)
byte my_iv[] = 
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
} ;

byte cipher [4*N_BLOCK] ; //size of cipher text
byte check [4*N_BLOCK] ;  

void setup ()
{
  Serial.begin (9600) ;
   
  Serial.println("Welcome to the Alpha E.K.G. Trojan! Brought to you by IronBit") ;
  Serial.println("Waiting for CIPHER text to decrypt (max 32 bytes)...") ;
  //These are just for the IOShield to be able to display the plaintext
  //OLED Display init
  IOShieldOled.begin();

  int irow;
  int ib;

  //Clear the virtual buffer
  IOShieldOled.clearBuffer();
  
  //Chosing Fill pattern 0
  IOShieldOled.setFillPattern(IOShieldOled.getStdPattern(0));
  //Turn automatic updating off
  //IOShieldOled.setCharUpdate(0);
  IOShieldOled.clearBuffer();
  IOShieldOled.setCursor(3,0);
  IOShieldOled.putString("Awaiting");
  IOShieldOled.setCursor(3,1);
  IOShieldOled.putString("Ciphered");
  IOShieldOled.setCursor(3,2);
  IOShieldOled.putString("Text...");
  //end IOShield init
  
  //Hold here until we read the ciphered text from the ALPHA system
  while(i<32)
  {
    while (Serial.available())
    {
      int alpha = Serial.read();
      Serial.print(alpha, HEX);  //debug print to verify incoming values
      Serial.print(" ");  
      cipher[i] = alpha;          //store ciphered text into array
      
      //this is to account for the dynamic key that changes depending on switch pattern
      if (i==-1){
        dynamic_key = alpha;
      }
      i++;
    }

  //once ciphered text finished verify array by printing it to the console  
  if (i==30) 
  {  
    Serial.print("\nTotal amount of ciphered text (bytes) received = ");
    Serial.println(i);
    Serial.print("Ciphered Text Store into cipher array: ");
      while(index_count<i)
      {
        Serial.print(cipher[index_count], HEX);
        Serial.print(" ");
        index_count++;
      }
    Serial.println(); //print newline to to make it pretty
    i=32;           //fix this later. Used to kill the loop and begin the decryption
   } //end if
 }//end while-hold for cipher text
   
   Serial.print("Alpha Switch Config: ");
   Serial.println(dynamic_key, BIN);
 
   //adjust the master key to account for the switch config
   //XOR MSB 8-bits and AND LSB 8-bits
   key[0] = key[0]^dynamic_key;
   key[15] = key[15]&dynamic_key;
   index_count = 0;
   
   //view new AES key 
   Serial.print("Dynamic Key: ");
   while(index_count<16)
   {
     Serial.print(key[index_count], HEX);
     Serial.print(" ");
     index_count++;
   }
   Serial.println(); //more new lines for prettyness 
   Serial.println();
   
prekey_test () ;
  
}

//AES Decryption 
void prekey (int bits, int blocks)
{
  byte iv [N_BLOCK] ;
  long t0 = micros () ;
  byte succ = aes.set_key (key, bits) ;
  long t1 = micros()-t0 ;
  
  //time required to obtain key (only really useful for encryption and key generation)
  Serial.print ("set_key ") ; Serial.print (bits) ; Serial.print (" ->") ; Serial.print ((int) succ) ;
  Serial.print (" took ") ; Serial.print (t1) ; Serial.println ("us") ;
  t0 = micros () ;
  
  //128 AES Decryption Begins here
  t0 = micros () ;
  if (blocks == 1)
    succ = aes.decrypt (cipher, plain) ;
  else
  {
    for (byte i = 0 ; i < 16 ; i++)
      iv[i] = my_iv[i] ;
    succ = aes.cbc_decrypt (cipher, check, blocks, iv) ;
  }
  t1 = micros () - t0 ;
  Serial.print ("decrypt # ") ; Serial.print ((int) succ) ;
  Serial.print (" took ") ; Serial.print (t1) ; Serial.println ("us") ;

  for (byte ph = 0 ; ph < (blocks == 1 ? 3 : 4) ; ph++)
  {
    for (byte i = 0 ; i < (ph < 3 ? blocks*N_BLOCK : N_BLOCK) ; i++)
    {
      byte val = ph == 0 ? plain[i] : ph == 1 ? cipher[i] : ph == 2 ? check[i] : iv[i] ;
      Serial.print (val>>4, HEX) ;
      Serial.print (val&15, HEX) ; 
      Serial.print (" ") ;
    }
    Serial.println ("") ;
  }
//display the plaintext on the OLED Screen 
IOShieldOled.clearBuffer();
IOShieldOled.setCursor(0,0);
IOShieldOled.putString("Your Plaintext:");
IOShieldOled.setCursor(0,1);

i=0;
  Serial.print("\nYour plaintext from the Alpha System is: ");
  while (i<30){
   char plain_text = plain[i];
   Serial.print(plain_text);
   IOShieldOled.putChar(plain_text);
    i++;
   };
  IOShieldOled.setCursor(0,3);
  IOShieldOled.putString("Nice Try though.");
  Serial.println("\n\nYou have just been decrypted without me ever touching your code. Better Luck Next Time ");
}

//bit and block size of AES
void prekey_test ()
{
  prekey (128, 1) ;
}

//one shot system so we won't use the infinite loop
void loop () 
{

}

