void TFT_update()
{
  tft.setCursor(0, 100);
//  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Ground State(ft): ");
   tft.fillRoundRect(0,108,40,15,0, ST7735_BLACK);
  tft.setTextSize(2);
 tft.setTextColor(ST7735_GREEN);
 tft.println(brightness);

//  tft.setTextColor(ST7735_WHITE);
//  tft.setTextSize(1);
//  tft.println("Average Velocity: ");
//  tft.setTextSize(2);
//  tft.setTextColor(ST7735_BLUE);
//  tft.println(avgVel, 2);
//  
//  tft.setTextColor(ST7735_WHITE);
//  tft.setTextSize(1);
//  tft.println("Current Altitude: ");
//  tft.setTextSize(2);
//  tft.setTextColor(ST7735_RED);
//  tft.println(altOld);
//  
//  tft.setTextColor(ST7735_WHITE);
//  tft.setTextSize(1);
//  tft.println("Predicted Ymax: ");
//  tft.setTextSize(2);
//  tft.setTextColor(ST7735_YELLOW);
//  tft.println(yMax, 2);
//  
//  tft.setTextColor(ST7735_WHITE);
//  tft.setTextSize(1);
//  tft.println("Doors opened at: ");
//  tft.setTextSize(2);
//  tft.setTextColor(ST7735_MAGENTA);
//  tft.println(LCD_open);
//  
//  tft.setTextColor(ST7735_WHITE);
//  tft.setTextSize(1);
//  tft.println("Doors Closed at: ");
//  tft.setTextSize(2);
//  tft.setTextColor(ST7735_BLUE);
//  tft.println(LCD_close);

}
