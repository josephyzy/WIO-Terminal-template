#include <Arduino.h>

#include "Free_Fonts.h" //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h
#include "TFT_eSPI.h"
#include "RTC_SAMD51.h"

// Set to 1 to print debug messages to serial
#define DEBUG 0

#define FONT FMB12 // See "include/Free_Fonts.h" for options

#define BUTTON_UP WIO_KEY_C
#define BUTTON_MID WIO_KEY_B
#define BUTTON_DOWN WIO_KEY_A

// Pages (features)
#define PAGES_MAX 2
#define PAGE_HOME 1
#define PAGE_DATE_TIME 2
#define PAGE_BATTERY 3

// Global variables
int pageToShow = PAGE_DATE_TIME;

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft); //Initializing buffer

RTC_SAMD51 rtc; // Real time clock
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// load page
void loadPage(String headerText, uint16_t headerTextCol, uint16_t headerBkgCol, uint16_t bkgCol);
int checkPageChangeNeeded();

void pageHome()
{
  loadPage("Home", TFT_BLACK, TFT_WHITE, TFT_GREENYELLOW);

  int pageChange = 0;
  while (pageChange == 0)
  {
    // Push to LCD
    spr.pushSprite(0, 0); //Push to LCD

    // Check if need to change page
    pageChange = checkPageChangeNeeded();
  }
}
void pageDateTime()
{
  loadPage("Date Time", TFT_BLACK, TFT_WHITE, TFT_DARKGREEN);

  int pageChange = 0;
  while (pageChange == 0)
  {
    String dateStr, dayStr, timeStr;
    DateTime now = rtc.now();

    // Date / Time
    dateStr = String("");
    dateStr = String(dateStr + now.day());
    dateStr = String(dateStr + "/");
    dateStr = String(dateStr + now.month());
    dateStr = String(dateStr + "/");
    dateStr = String(dateStr + now.year());

    dayStr = String("");
    dayStr = String(dayStr + daysOfTheWeek[now.dayOfTheWeek()]);

    timeStr = String("");
    timeStr = String(timeStr + now.hour());
    timeStr = String(timeStr + ":");
    if (now.minute() < 10)
    {
      timeStr = String(timeStr + "0");
    }
    timeStr = String(timeStr + now.minute());
    timeStr = String(timeStr + ":");
    if (now.second() < 10)
    {
      timeStr = String(timeStr + "0");
    }
    timeStr = String(timeStr + now.second());

    spr.fillRect(0, 30, 240, 320, TFT_DARKGREEN); // Clear region

    spr.setFreeFont(FMB18);
    spr.drawString(dateStr, 10, 100);
    spr.drawString(dayStr, 10, 150);
    spr.drawString(timeStr, 10, 200);

    // Set back to default font
    spr.setFreeFont(FONT);

    // Push to LCD
    spr.pushSprite(0, 0); //Push to LCD

    // Check if need to change page
    pageChange = checkPageChangeNeeded();
  }
}

// put your setup code here, to run once:
void setup()
{
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(2);

  spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

  rtc.begin();
  DateTime now = DateTime(F(__DATE__), F(__TIME__));
  //!!! notice The year is limited to 2000-2099
  if (DEBUG)
  {
    Serial.println("adjust time!");
  }
  rtc.adjust(now);
}

// put your main code here, to run repeatedly:
void loop()
{
  switch (pageToShow)
  {
  case PAGE_HOME:
    pageHome();
    break;
  case PAGE_DATE_TIME:
    pageDateTime();
    break;
  default:
    break;
  }
}

void loadPage(String headerText, uint16_t headerTextCol, uint16_t headerBkgCol, uint16_t bkgCol)
{
  spr.fillSprite(bkgCol); //Fill background

  spr.fillRect(0, 0, 240, 30, headerBkgCol); // Header portion
  spr.setFreeFont(FONT);
  //  spr.setTextSize(1);
  spr.setTextColor(headerTextCol);
  spr.drawString(headerText, 5, 6);

  unsigned int rowHeight = 20;
  unsigned int topMargin = 33;
  unsigned int leftMargin = 0;
  for (unsigned int i = 0; i < 13; i++)
  {
    spr.drawString("Ln " + String(i) + " posY = " + String(topMargin + i * rowHeight), leftMargin, topMargin + i * rowHeight);
  }

  spr.drawString("01234567890123456789", leftMargin, 293);

  spr.pushSprite(0, 0); //Push to LCD
}

int checkPageChangeNeeded()
{
  if (DEBUG)
  {
    Serial.print("pageToShow = ");
    Serial.println(pageToShow);
  }
  if (digitalRead(BUTTON_UP) == LOW)
  {
    if (DEBUG)
    {
      Serial.println("Up Key pressed");
    }
    if (pageToShow == 1)
    {
      pageToShow = PAGES_MAX;
    }
    else
    {
      pageToShow -= 1;
    }
    delay(250);
    return 1;
  }
  else if (digitalRead(BUTTON_MID) == LOW)
  {
    if (DEBUG)
    {
      Serial.println("Mid Key pressed");
    }
    pageToShow = PAGE_HOME;
    delay(250);
    return 1;
  }
  else if (digitalRead(BUTTON_DOWN) == LOW)
  {
    if (DEBUG)
    {
      Serial.println("Down Key pressed");
    }
    if (pageToShow == PAGES_MAX)
    {
      pageToShow = 1;
    }
    else
    {
      pageToShow += 1;
    }
    delay(250);
    return 1;
  }
  else
  {
    return 0;
  }
}