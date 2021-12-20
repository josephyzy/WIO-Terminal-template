#include <Arduino.h>

#include "TFT_eSPI.h"
#include "Free_Fonts.h"   //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h

#define FONT FMB12    // See "include/Free_Fonts.h" for options

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);    //Initializing buffer

void loadPage(String headerText, uint16_t headerTextCol, uint16_t headerBkgCol, uint16_t bkgCol);

void setup()
{
  // put your setup code here, to run once:
  tft.begin();
  tft.setRotation(2);

  spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

}

void loop()
{
  // put your main code here, to run repeatedly:

  loadPage("Home", TFT_BLACK, TFT_WHITE, TFT_GREENYELLOW);

}

void loadPage(String headerText, uint16_t headerTextCol, uint16_t headerBkgCol, uint16_t bkgCol)
{
  spr.fillSprite(bkgCol); //Fill background

  spr.fillRect(0, 0, 240, 30, headerBkgCol); // Header portion
  spr.setFreeFont(FONT);
//  spr.setTextSize(1);
  spr.setTextColor(headerTextCol);
  spr.drawString(headerText, 5, 6);

  spr.pushSprite(0, 0); //Push to LCD
}