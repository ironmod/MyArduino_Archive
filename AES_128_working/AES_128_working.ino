#include <AES.h>

AES aes ;
int i = -1;
int index = 0;

byte key[] = 
{
  0xFB, 0x79, 0x15, 0xBD, 0xF1, 0xE5, 0xC8, 0xB8, 0x4B, 0xB7, 0x18, 0xDD, 0x34, 0xD7, 0x33, 0x00,
  //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
} ;

byte plain[] =
{
  // 0xf3, 0x44, 0x81, 0xec, 0x3c, 0xc6, 0x27, 0xba, 0xcd, 0x5d, 0xc3, 0xfb, 0x08, 0xf2, 0x73, 0xe6
 // 0x68, 0x61, 0x72, 0x64, 0x77, 0x61, 0x72, 0x65, 0x73, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79,
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

void loop () 
{}


void setup ()
{
  Serial.begin (9600) ;
  Serial.print ("testng mode") ;

  
  while(i<32){
   while (Serial.available())
    {
      int alpha = Serial.read();
      Serial.println(alpha, HEX);
      cipher[i] = alpha;
      i++;
    }
  if (i==30){
    Serial.print("I = ");
    Serial.println(i);
    while(index<i){
      Serial.println(cipher[index], HEX);
      index++;
    }
    i=32;
  }
 }//end while-hold
  prekey_test () ;
  
}



void prekey (int bits, int blocks)
{
  byte iv [N_BLOCK] ;
  
  long t0 = micros () ;
  byte succ = aes.set_key (key, bits) ;
  long t1 = micros()-t0 ;
  
  Serial.print ("set_key ") ; Serial.print (bits) ; Serial.print (" ->") ; Serial.print ((int) succ) ;
  Serial.print (" took ") ; Serial.print (t1) ; Serial.println ("us") ;
  t0 = micros () ;
  /*if (blocks == 1)
    succ = aes.encrypt (plain, cipher) ;
  else
  {
    for (byte i = 0 ; i < 16 ; i++)
      iv[i] = my_iv[i] ;
    succ = aes.cbc_encrypt (plain, cipher, blocks, iv) ;
  }
  t1 = micros () - t0 ;
  Serial.print ("encrypt ") ; Serial.print ((int) succ) ;
  Serial.print (" took ") ; Serial.print (t1) ; Serial.println ("us") ;
  */
  
  //128 AES
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
  Serial.print ("decrypt ") ; Serial.print ((int) succ) ;
  Serial.print (" took ") ; Serial.print (t1) ; Serial.println ("us") ;

  for (byte ph = 0 ; ph < (blocks == 1 ? 3 : 4) ; ph++)
  {
    for (byte i = 0 ; i < (ph < 3 ? blocks*N_BLOCK : N_BLOCK) ; i++)
    {
      byte val = ph == 0 ? plain[i] : ph == 1 ? cipher[i] : ph == 2 ? check[i] : iv[i] ;
      Serial.print (val>>4, HEX) ; Serial.print (val&15, HEX) ; Serial.print (" ") ;
    }
    Serial.println () ;
  }

}

void prekey_test ()
{
  prekey (128, 4) ;
  //prekey (192, 3) ;
  //prekey (256, 2) ;
  prekey (128, 1) ;
  //prekey (192, 1) ;
  //prekey (256, 1) ;
}


