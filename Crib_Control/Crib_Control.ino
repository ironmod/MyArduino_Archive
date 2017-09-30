#define sclk 13
#define mosi 11
#define cs   10
#define dc   9
#define rst  8  // you can also connect this to the Arduino reset

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

int analogMeter0 = 0;
int analogMeter2 = 0;
int analogMeter3 = 0;
int analogMeter4 = 0;
int analogMeter5 = 0;
int analogMeter1 = 0;
int pwm1 = 0;
int pwm2 = 0;
int pwm3 = 0;
int pwm4 = 0;
int pwm5 = 0; 
int pwm6 = 0;
int pwm7 = 0;

int RGB1_SW = 4;
int FADE_SW = 2;
int PIR_SENSOR = 8;
int R2 = 3;
int G2 = 5;
int B2 = 6;
 
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

char tftMode = 0;

void setup(){
  setAll_OUTPUT(); //set all IO 
  Serial.begin(9600);
  Serial.println("Starting...");
  
//initiliaze the TFT screen
   tft.initR(INITR_REDTAB); 
  Serial.println("init");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  tft.fillScreen(ST7735_BLACK);
  testdrawtext("Welcome to the danger zone...", ST7735_WHITE);
  delay(1000);

}

void loop(){


  
//Motion activated PIR Sensor  
  if (digitalRead(PIR_SENSOR) == HIGH)
  {
    PIR_MODE();
    tftMode='PIR';
  }
  
//Use this for if you want to manually control the RGB states
 else if (digitalRead(RGB1_SW) == HIGH)
  {
    RGB1_MODE();
    tftMode='RGB1';
  }

 //Fading LED Mode
//   else if(digitalRead(FADE_SW)==HIGH)
//     {
//        FADE_MODE();
//        tftMode='FADE';
//     }
     
 //turn off all the lighitng    
   else
    {
      fade_off();
      tftMode='OFF';
    }
   TFT_update();
   //delay(2000);
}




