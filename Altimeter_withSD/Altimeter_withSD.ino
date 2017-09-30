#include <math.h>
#include <SD.h>

const int chipSelect=10; //SD card select 
long altOld =0L;        //old altimeter reading to be used for velocity
long New_Vel=0L;        //current velocity
long Prev_Vel=0L;       //previous velocity
long openAlt=0L;        //altitude the doors opened
long closeAlt=0L;       //altitude the doors closed
long altRecord=0L;      //altitude recorded
float vAvg=0;           //average velocity for accuracy
float average=0;        //New_Vel+Prev_Vel
float VtSq=392;         // Vt^2
float VtMult=6;         // (Vt^2)/2g
float lnConst=0;        //ln((vAvg + VtSq)/VtSq)
float yMax=0;           //yMax=VtMult*ln(lnConst)+altNew
double lnValue=0;       //nat log to be used for yMax prediction
int relayOpen=3;        //pin select to trigger Relay to open doors
int relayClose=4;       //pin select to trigger Relay to close doors
long altGround=0L;      //altitude above Sea Level (ground state)
void setup() 
{
  Serial.begin(9600);
  Serial.println("Rocket Power!");
  pinMode(relayOpen, OUTPUT);
  pinMode(relayClose, OUTPUT);
  digitalWrite(relayOpen, HIGH);    //make sure Relay modules are turned off
  digitalWrite(relayClose, HIGH);   
  //PreConditions: alt_value is the value the alitmeter is currently sitting at. During the
  //startup process, it will calculate the (ft) the altimeter is sitting at above Sea Level
  //depending on the location (130-160ft Orlando, 500-600ft Alabama)
  //Post Conditions: Once the ft above sea level has been calculated, 
  //the alitmeter value will be >0, breaking out of the first while loop and exectue the code
  while (1) 
  {        
   char alt_data = 0;
   long alt_value = 0L;
   
     while(1) //waiting for ground state to calculate. 
      {
         if(!Serial.available())
         continue;
    
         alt_data = Serial.read();
         if((alt_data < '0')|| (alt_data > '9')) //makes sure the arduino is only transfering
         {                                     //8 bits of data '0'=0x30 '9'=0x38 in ASCII
           break;
         }
         else
         {
          alt_value = alt_value*10 + (alt_data - '0');
         }
       }//end while reading altimeter data
    if(alt_value != 0)
    {
      alt_value=altGround;
     break;
    } 
  }//end while checking for ground state
  Serial.print("Ground state is (ft): ");
  Serial.println(altGround);
  Serial.flush();
  delay(10);
  
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


//Read the altitude from the altimeter and return the value to void loop()
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
  }//end while loop reading altimeter data
  
  return alt_value;
  
}//end altitudeRead

void datalog()
{
   String dataString= "";
   dataString += String(altRecord);
   dataString += String(altOld);
   dataString += String(New_Vel);
   dataString += String(Prev_Vel);
   dataString += String(openAlt);
   dataString += String(closeAlt);
   File dataFile = SD.open("datalog.txt", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }   
}//end datalog

void loop()
{
  long altNew=altitudeRead();
  if (altNew !=0 )
  {
    New_Vel=altNew-altOld;       //update new velocity 
    altOld=altNew;               //update old altitude reading
    average=New_Vel+Prev_Vel;    
    vAvg=average/2;              //get average velocity for accuracy
    Prev_Vel=New_Vel;            //update old velocity reading
    
     Serial.print("Updated Altitude 1: ");
     Serial.println(altNew);
     Serial.println(" ");
      if (altNew > 3)      //ONLY start when YMax needs to start predicting
      {
         lnConst= vAvg + VtSq;  
         lnConst= lnConst/VtSq;
         lnValue = log(lnConst);
         yMax=lnValue*VtMult;
         yMax=yMax + altNew;
         //activates the doors/Relay Module to open the doors
         if (yMax > 7)  
         {
           digitalWrite(relayClose, HIGH);
           delay(1);
           digitalWrite(relayOpen, LOW);
           openAlt=altNew;
         }
          //triggers the relay module to close the doors
          //only if the doors have been triggered to open
         if ( (yMax <= 7) && (digitalRead(relayClose)==0)) 
         {                                               
           digitalWrite(relayOpen, HIGH);             
           delay(1);
           digitalWrite(relayClose, LOW);
           closeAlt=altNew;
         }
      }//end yMax if  
   }//end altitude if 
  Serial.flush();    //clean the data
  
  altRecord=altNew;
  datalog();        //write data to SD card
}//end loop
