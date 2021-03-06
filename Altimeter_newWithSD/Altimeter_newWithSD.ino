#include "math.h"
#include <SD.h>

const int chipSelect=10; //SD card select 
long altNew =0L;
long altOld =0L;
long newVel=0L;
long preVel=0L;
float avgVel=0;
long altGround=0L;
int relayOpen=3;    //relay module trigger on Digial Pin 3
int relayClose=4;   //relay module trigger on Digital Pin 4

 /* PreConditions: alt_value is the value the alitmeter is currently sitting at. During the
      startup process, it will calculate the (ft) the altimeter is sitting at above Sea Level
      depending on the location (130-160ft Orlando, 500-600ft Alabama)
  Post Conditions: Once the ft above sea level has been calculated, 
      the alitmeter value will be >0, breaking out of thvae first while loop and exectue the code
*/
void setup() 
{
  Serial.begin(9600);
  Serial.println("Rocket Power!");
  pinMode(relayOpen, OUTPUT);
  pinMode(relayClose, OUTPUT);
  digitalWrite(relayOpen, HIGH);
  digitalWrite(relayClose, HIGH);
  altGround=altitudeRead();
  Serial.print("Ground State in (ft): ");
  Serial.println(altGround);
  
    //SD Card Reader initiliaztion
  Serial.print("Initializing SD card...");
     pinMode(10, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Check SD Card. (corrupted or not inserted)");
    return;
  }
  Serial.println("SD card initialized."); 
  Serial.flush();
  delay(10);
}//end setup

//infinite loop checking states the rocket is at to predict when to open the 
//doors to slow the rocket down and when to close them
void loop()
{
  altNew=altitudeRead();
  if (altNew !=0 )
  {
     newVel=altNew-altOld;
  // Serial.print("Updated Altitude 1: ");
   //Serial.println(altNew);
   //Serial.print("Altitude Old: ");
   //Serial.println(altOld);
      altOld=altNew;
      avgVel=newVel+preVel;
      avgVel=avgVel/2;
      preVel=newVel;
   
   //Serial.print("Average Velocity: ");
   //Serial.println(avgVel);
   //once the rocket rises above 4,000 feet, we need to begin
   //predicting what the next height will be 
    if (altNew > 4200) 
    {
       prediction();
    }  
   Serial.println(" ");
   datalog();
  }

  Serial.flush();  //clean the data
  delay(10);       //10ms sampling rate
}//end void loop

//Reading in the altitude from the Altimeter and converting it from ASCII to integer
long altitudeRead()
{
  char alt_data = 0;
  long alt_value = 0L;
  while(1)
  {
    if(!Serial.available())
      continue;
    
      alt_data = Serial.read();
      if((alt_data < '0')|| (alt_data > '9')) //makes sure the arduino is only transfering
        {                                     //8 bits of numerical data '0'=0x30 '9'=0x38 in ASCII
          break;
        }
        else
        {
          alt_value = alt_value*10 + (alt_data - '0'); //converts ASCII to readable integer
        }
  }
  return alt_value;
}

//Predict the next height the rocket will be at
void prediction()    
{
float VtSq=392;      // Vt^2
float VtMult=6;      // (Vt^2)/2g
float lnConst=0;     //ln((avgVel + VtSq)/VtSq)
float yMax=0;        //yMax=VtMult*ln(lnConst)+altNew
double lnValue=0;

   lnConst= avgVel + VtSq;  
   lnConst= lnConst/VtSq;
   lnValue = log(lnConst);
   yMax=lnValue*VtMult;
   yMax=yMax + altNew;
   
   Serial.print("Ymax= ");
   Serial.println(yMax);
 
 //once the equation has predicted that the rocket will be at 5280 feet
 //we need to open the doors to slow it down. Once the Rocket has hit the 1 mile marker
 //we wll then shut the doors to allow steady free fall
 if (yMax > 5280)  //activates the doors/Relay Module
  {
    digitalWrite(relayClose, HIGH);
    delay(1);
    digitalWrite(relayOpen, LOW);
    Serial.print("Doors opened at (ft): ");
    Serial.println(altNew);
  }
 if ( (yMax <= 5280) && (digitalRead(relayOpen)==0)) 
  {                                              
    digitalWrite(relayOpen, HIGH);             
    delay(1);
    digitalWrite(relayClose, LOW);
    Serial.print("Doors closed at (ft): ");
    Serial.println(altNew);
  }
  Serial.flush();
  return;
}

//save all the data onto an SD card
void datalog()
{
   String dataString= "";
   dataString += String(altNew);
   dataString += ",";
//   dataString += String(altOld);
   dataString += String(newVel);
 //  dataString += String(preVel);
   //dataString += String(openAlt);
   //dataString += String(closeAlt);
   File dataFile = SD.open("datalog.txt", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }   
  Serial.flush();
}//end datalog
