#include <AES.h>

AES aes ;  
int i = -1;                //index counter for the incoming ciphered text. Start at -1 because the first 8 bits are the switch config
int index = 0;              
byte dynamic_key = 0x00;   //dynamic key to hold the switch pattern
//int bits = 128;            //128 bit AES 
//int blocks = 1;            //1 block (can hold up to 4)

byte key[16] = 
{
  0xFB, 0x79, 0x15, 0xBD, 0xF1, 0xE5, 0xC8, 0xB8, 0x4B, 0xB7, 0x18, 0xDD, 0x34, 0xD7, 0x33, 0xA5,
} ;

byte plain[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;

byte my_iv[] = 
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
} ;

byte cipher [4*N_BLOCK] ;
byte check [4*N_BLOCK] ;

void setup ()
{
  Serial.begin (9600) ;
  Serial.println("Welcome to the Alpha E.K.G. Trojan! Brought to you by IronBit") ;
  Serial.println("Waiting for CIPHER text to decrypt (max 32 bytes)...") ;
  
  //Hold here until we read the ciphered text from the ALPHA system
  while(i<32){
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
      while(index<i)
      {
        Serial.print(cipher[index], HEX);
        Serial.print(" ");
        index++;
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
   index = 0;
   
   //view new AES key 
   Serial.print("Dynamic Key: ");
   while(index<16)
   {
     Serial.print(key[index], HEX);
     Serial.print(" ");
     index++;
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


i=0;
  Serial.print("\nYour plaintext from the Alpha System is: ");
  while (i<30){
   char plain_text = plain[i];
   Serial.print(plain_text);
    i++;
   };
  
  Serial.println("\n\nYou have just been decrypted without me ever touching your code. Better Luck Next Time ");
}

//bit and block size of AES
void prekey_test ()
{
  prekey (128, 1) ;
}



//one shot system so we won't use the infinite loop
void loop () 
{}

