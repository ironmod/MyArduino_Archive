/*  NASA USLI Spring 2013 
    Team Rocket Power
    University of Central Florida 
    Reverse Flow Airbrake Electronics Control System
          Matthew Harrison-Program Manager
          Sean DelVecchio-Technical Operations Manager
          Jeff Leins-Flight Process Engineer
          Monica Bertram-Performance Engineer
          Ron Hofer-Mechanical Design Engineer
          Steven Darrow-Aerospace Design Engineer
          Dr. Marcel Ilie-Senior Design Team Advisor
          Mr. Joshua Steele-Electrical Team Advisor
          Mr. Brandon Frazer-Electrical Team Advisor
*/

#define cs   8    //Arduino pin 8 to CS on SparkFun SD Module 
#include "math.h"
#include <SD.h>

//Arduino pin 13 to SCL pin TFT module; pin 11 to SDA pin TFT module
const int chipSelect=8; //SD card select 
unsigned long altNew =0L;        //altitude value being read from stratologger
unsigned long altOld =0L;        //previous altitude used for average
unsigned long altGround=0L;      //ground state altitude 
float newVel=0L;         //Current Velocity
float preVel=0L;         //Previous Velocity used for average
float avgVel=0;         //average velocity
long SD_close =0L;      //Altitude the doors closed at written to the SD card
long SD_open =0L;       //Altitude the doors opened at written to the SD card
int relayOpen_pos=2;     //relay module trigger Digital Pin 2
int relayOpen_neg=4;     //relay module trigger Digital Pin 3
int relayClose_pos=3;    //relay module trigger Digital Pin 4
int relayClose_neg=5;    //relay module trigger Digital Pin 5
float VtSq=392;          // Vt^2
float VtMult=6;          // (Vt^2)/2g
float lnConst=0;         //ln((avgVel + VtSq)/VtSq)
float yMax=0;            //yMax=VtMult*ln(lnConst)+altNew
double lnValue=0;        //initiliaze lnValue to zero
int feedbackValue = 0;   //Value read in from the actuator feedback used for comparison
int feedbackPin = A0;    //actuator feedback (yellow wire) connected to pin A0 (other 2 wires are +5V and Ground)
int trigger_check =0;    //counter to see if doors have trigger open
int brake_altitude=5280; //predicted height to open the doors
int actuator_limit=800;  //how far to let the actuator extend 

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
  pinMode(relayOpen_pos, OUTPUT);
  pinMode(relayOpen_neg, OUTPUT);
  pinMode(relayClose_pos, OUTPUT);
  pinMode(relayClose_neg, OUTPUT);
  digitalWrite(relayOpen_pos, HIGH);
  digitalWrite(relayOpen_neg, HIGH);
  
  //Make sure doors are shut before takeoff
  digitalWrite(relayClose_pos, LOW);
  digitalWrite(relayClose_neg, LOW);
  delay(3000);
  digitalWrite(relayClose_pos, HIGH);
  digitalWrite(relayClose_neg, HIGH);
  
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
  
  feedbackValue=analogRead(feedbackPin);
  Serial.println("Initial Actuator Feedback Value: ");
  Serial.println(feedbackValue);
  
  Serial.flush();
  }//end setup

//infinite loop checking states the rocket is at to predict when to open the 
//doors to slow the rocket down and when to close them
void loop()
{
  feedbackValue=analogRead(feedbackPin);
  altOld=altNew;
       Serial.print("Updated Altitude 1loop: ");
       Serial.println(altNew);
       Serial.print("Altitude Oldloop: ");
       Serial.println(altOld);
       Serial.println(" ");
  altNew=altitudeRead();
  if (altNew !=0 )
  {
     newVel=(altNew-altOld)/(.05);
     //don't bother printing new statements unless the Rocket is moving
     if (altOld!=altNew)
     {
       Serial.print("Updated Altitude 1: ");
       Serial.println(altNew);
       Serial.print("Altitude Old: ");
       Serial.println(altOld);
     }
      avgVel=newVel+preVel;
      avgVel=avgVel/2;
      
     //only print if rocket is moving
     if (preVel!=newVel)
     {
       Serial.print("Average Velocity: ");
       Serial.println(avgVel);   
     }
     preVel=newVel;
     
   //once the rocket rises above 4,000 feet, we need to begin
   //predicting what the next height will be 
    if (altNew > 4200) 
    {
       prediction();
    }
    
  //datalog();  
  }
  Serial.flush();  //clean the data  
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
//and open the doors to slow it down
void prediction()    
{
lnConst=0;     
yMax=0;        
lnValue=0;

   lnConst= avgVel + VtSq;  
   lnConst= lnConst/VtSq;
   lnValue = log(lnConst);
   yMax=lnValue*VtMult;
   yMax=yMax + altNew;
   
   Serial.print("Ymax= ");
   Serial.println(yMax);
 //once the equation has predicted that the rocket will be at 5280 feet
 //we need to open the doors to slow it down. Once the Rocket has hit the 1 mile marker
 //we will then shut the doors to allow steady free fall
 if (yMax > brake_altitude && digitalRead(relayOpen_pos)==1 && abs(yMax)<15000)  //activates the doors/Relay Module
  {
    digitalWrite(relayClose_pos, HIGH);
    digitalWrite(relayClose_neg, HIGH);
    delay(1);
    
    //while loop makes sure the actuator does not extend past set limit
    feedbackValue=analogRead(feedbackPin);
   while(feedbackValue>actuator_limit)
    {
      feedbackValue=analogRead(feedbackPin);
        digitalWrite(relayOpen_pos, LOW);
        digitalWrite(relayOpen_neg, LOW);
      Serial.print("Doors opened at (ft): ");
      Serial.println(altNew);
      SD_open=altNew;
      trigger_check=1;
    }
    
    //turn of the motor and hold in place once 
    //actuator feedback limit has been reached
    if(trigger_check==1){
      feedbackValue=analogRead(feedbackPin);
      digitalWrite(relayOpen_pos, HIGH);
      digitalWrite(relayOpen_neg, HIGH);
      Serial.println("Doors Stopped (reading from actuator feedback):");
      Serial.println(feedbackValue);
    }
   }
   
  //close doors and hold shut until landing
 if (yMax <= brake_altitude && digitalRead(relayOpen_pos)==1 && trigger_check==1) 
  {                                              
    digitalWrite(relayOpen_pos, HIGH);
    digitalWrite(relayOpen_neg, HIGH);    
    delay(1);
    digitalWrite(relayClose_pos, LOW);
    digitalWrite(relayClose_neg, LOW);
    Serial.print("Doors closed at (ft): ");
    Serial.println(altNew);
    SD_close=altNew;
  }
// datalog(); //log on the data onto the SD card
  Serial.flush();
  return;
}

//save all the data onto an SD card
void datalog()
{
  int sdYmax=yMax;//yMax can not be a floating point # to print to SD card 
  String dataString= "";
  dataString += String(altNew);
  dataString += ",";
  dataString += String(newVel);
  dataString += ",";
  dataString += String(SD_open);
  dataString += ",";
  dataString += String(sdYmax);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }  
}//end datalog 







