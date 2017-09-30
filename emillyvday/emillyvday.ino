 /*
 This sketch demonstrates the use of the autoscroll()
 and noAutoscroll() functions to make new text scroll or not.
 
 based on the Autoscroll example, included
 in the LiquidCrystal Arduino Library
 */
 
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TKLCD.h>

const int EXAMPLES_DELAY = 5000;

//TKLCD_Twi lcd = TKLCD_Twi();
TKLCD_Serial lcd = TKLCD_Serial(); //for Arduino Mega and Mega ADK write
//TKLCD_Serial lcd = TKLCD_Serial(x); where x is the number of the
//serial connector you want to use (x = 1, 2,3 or 4)

/*If you want to modify the address of I2C communication use the function
 lcd.setActiveAddress(NEW_ADDRESS);
 
 Default address is 0x33*/

void setup() {
  lcd.begin();
  lcd.print("                ");
  lcd.print("                ");
}

void loop() {
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);

 /*
 E: Energetic
 M: Magical
 I: Inspiring
 L: Loving
 Y: Youthful
 */
 
 lcd.print("   E.M.I.L.Y.");
 delay(2000);
 lcd.setCursor(0,1);
 lcd.print("E:");
 lcd.print("Energetic");
 delay(2000);
  lcd.setCursor(0,1);
  lcd.print("M: Magical  ");
  delay(2000);
   lcd.setCursor(0,1);
 lcd.print("I: Inspiring"); 
 delay(2000);
  lcd.setCursor(0,1);
 lcd.print("L: Loving <3 ");
 delay(2000);
  lcd.setCursor(0,1);
 lcd.print("Y: Youthfull");
 delay(2000);
 lcd.setCursor(0,0);
lcd.print("awesome cookies....nom nom    ");
 delay(2000);
 lcd.setCursor(0,0);
 lcd.print("Happy VDAY 2014 ");
 lcd.setCursor(0,1);
 lcd.print("<3 BF NT TD    ");
 delay(5000);
  // turn off automatic scrolling
 // lcd.noAutoscroll();
  
  // clear screen for the next loop:
  lcd.clear();
}

