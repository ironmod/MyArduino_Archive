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

//pin assignments will change once I figure out how to interface
//the SEEED studio SD module and the Screen together
#define cs   10    //Arduino pin 10 to CS TFT module
#define dc   9     //Arduino pin 9 to DC TFT module
#define rst  8     // you can also connect this to the Arduino reset
#include "math.h"
#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library for TFT
#include <Adafruit_ST7735.h> // Hardware-specific library for TFT
#include <SPI.h>             //comm. protocol for TFT

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
//Arduino pin 13 to SCL pin TFT module; pin 11 to SDA pin TFT module
const int chipSelect=6; //SD card select 
long altNew =0L;
long altOld =0L;
long altGround=0L;
long newVel=0L;
long preVel=0L;
float avgVel=0;
long LCD_close =0L;
long LCD_open =0L;
int relayOpen_pos=2;   //relay module trigger Digital Pin 2
int relayOpen_neg=3;   //relay module trigger Digital Pin 3
int relayClose_pos=4;  //relay module trigger Digital Pin 4
int relayClose_neg=5;  //relay module trigger Digital Pin 5
float VtSq=392;      // Vt^2
float VtMult=6;      // (Vt^2)/2g
float lnConst=0;     //ln((avgVel + VtSq)/VtSq)
float yMax=0;        //yMax=VtMult*ln(lnConst)+altNew
double lnValue=0;

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
  digitalWrite(relayClose_pos, HIGH);
  digitalWrite(relayClose_neg, HIGH);
  
  altGround=altitudeRead();
  Serial.print("Ground State in (ft): ");
  Serial.println(altGround);
  
tft.initR(INITR_REDTAB);
  Serial.println("initializing LCD...");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;
  // initialize LCD
   //tft.setCursor(0, 0);
  //tft.fillScreen(ST7735_BLACK);
  LCD_print();
  delay(4000);

  Serial.println("done");
  delay(1000);

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
     //don't bother printing new statements unless the Rocket is moving
     if (altOld!=altNew)
     {
       Serial.print("Updated Altitude 1: ");
       Serial.println(altNew);
       Serial.print("Altitude Old: ");
       Serial.println(altOld);
     }
      altOld=altNew;
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
  }
  Serial.flush();  //clean the data
  LCD_print();
  delay(10); //10ms sampling rate
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
 //we wll then shut the doors to allow steady free fall
 if (yMax > 5280 && digitalRead(relayOpen_pos)==1)  //activates the doors/Relay Module
  {
    digitalWrite(relayClose_pos, HIGH);
    digitalWrite(relayClose_neg, HIGH);
    delay(1);
    digitalWrite(relayOpen_pos, LOW);
    digitalWrite(relayOpen_neg, LOW);
    Serial.print("Doors opened at (ft): ");
    Serial.println(altNew);
    LCD_open=altNew;
  }
 if (yMax <= 5280 && digitalRead(relayOpen_pos)==0) 
  {                                              
    digitalWrite(relayOpen_pos, HIGH);
    digitalWrite(relayOpen_neg, HIGH);    
    delay(1);
    digitalWrite(relayClose_pos, LOW);
    digitalWrite(relayClose_neg, LOW);
    Serial.print("Doors closed at (ft): ");
    Serial.println(altNew);
    LCD_close=altNew;
  }
  datalog(); //log on the data onto the SD card
  Serial.flush();
  return;
}


//save all the data onto an SD card
void datalog()
{
   String dataString= "";
   dataString += String(altNew);
   dataString += String(altOld);
   dataString += String(newVel);
   dataString += String(preVel);
   //dataString += String(openAlt);
   //dataString += String(closeAlt);
   File dataFile = SD.open("datalog.txt", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }   
}//end datalog

//update values on LCD screen 
void LCD_print()
{
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Ground State(ft): ");
  tft.setTextSize(2);
  tft.setTextColor(ST7735_GREEN);
  tft.println(altGround);
  
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Average Velocity: ");
  tft.setTextSize(2);
  tft.setTextColor(ST7735_BLUE);
  tft.println(avgVel, 2);
  
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Current Altitude: ");
  tft.setTextSize(2);
  tft.setTextColor(ST7735_RED);
  tft.println(altOld);
  
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Predicted Ymax: ");
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.println(yMax, 2);
  
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Doors opened at: ");
  tft.setTextSize(2);
  tft.setTextColor(ST7735_MAGENTA);
  tft.println(LCD_open);
  
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Doors Closed at: ");
  tft.setTextSize(2);
  tft.setTextColor(ST7735_BLUE);
  tft.println(LCD_close);

}
