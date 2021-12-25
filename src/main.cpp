#include <Arduino.h>

#include "Free_Fonts.h" //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h
#include "TFT_eSPI.h"

#include <Page_Home.h>
#include <Page_Date_Time.h>
#include <Page_Temp_Humi.h>
#include <Page_Word_Colour_Match_Game.h>
#include <Page_Battery.h>

// Pages (features)
#define PAGES_MAX 5
#define PAGE_HOME 1
#define PAGE_DATE_TIME 2
#define PAGE_TEMP_HUMI 3
#define PAGE_WORD_COLOUR_MATCH_GAME 4
#define PAGE_BATTERY 5

// Set to 1 to print debug messages to serial
#define DEBUG 0

#define FONT FMB12 // See "include/Free_Fonts.h" for options

// Remap to suit orientation (tft.setRotation(2))
#define JOYSTICK_PRESS WIO_5S_PRESS
#define JOYSTICK_UP WIO_5S_LEFT
#define JOYSTICK_DOWN WIO_5S_RIGHT
#define JOYSTICK_LEFT WIO_5S_DOWN
#define JOYSTICK_RIGHT WIO_5S_UP
#define BUTTON_TOP WIO_KEY_C
#define BUTTON_MID WIO_KEY_B
#define BUTTON_BOT WIO_KEY_A

// Global variables
int pageToShow = PAGE_WORD_COLOUR_MATCH_GAME;

// Volatile variables for interrupt service routine
volatile int joystickPressPressed = 0;
volatile int joystickUpPressed = 0;
volatile int joystickDownPressed = 0;
volatile int joystickLeftPressed = 0;
volatile int joystickRightPressed = 0;
volatile int buttonTopPressed = 0;
volatile int buttonMidPressed = 0;
// limitation // volatile int buttonBotPressed = 0;

// Interrup service routines
void ISR_JOYSTICK_PRESS() { joystickPressPressed = 1; }
void ISR_JOYSTICK_UP() { joystickUpPressed = 1; }
void ISR_JOYSTICK_DOWN() { joystickDownPressed = 1; }
void ISR_JOYSTICK_LEFT() { joystickLeftPressed = 1; }
void ISR_JOYSTICK_RIGHT() { joystickRightPressed = 1; }
void ISR_BUTTON_TOP() { buttonTopPressed = 1; }
void ISR_BUTTON_MID() { buttonMidPressed = 1; }
// limitation. Only either buttonBot OR WIO_5S_UP.. but not both..
// void ISR_BUTTON_BOT() { buttonBotPressed = 1; }

TFT_eSPI tft;

RTC_SAMD51 rtc; // Real time clock

void updatePageToShow();

// put your setup code here, to run once:
void setup()
{
  pinMode(JOYSTICK_PRESS, INPUT_PULLUP);
  pinMode(JOYSTICK_UP, INPUT_PULLUP);
  pinMode(JOYSTICK_DOWN, INPUT_PULLUP);
  pinMode(JOYSTICK_LEFT, INPUT_PULLUP);
  pinMode(JOYSTICK_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_TOP, INPUT_PULLUP);
  pinMode(BUTTON_MID, INPUT_PULLUP);
  pinMode(BUTTON_BOT, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(JOYSTICK_PRESS), ISR_JOYSTICK_PRESS, LOW);
  attachInterrupt(digitalPinToInterrupt(JOYSTICK_UP), ISR_JOYSTICK_UP, LOW);
  attachInterrupt(digitalPinToInterrupt(JOYSTICK_DOWN), ISR_JOYSTICK_DOWN, LOW);
  attachInterrupt(digitalPinToInterrupt(JOYSTICK_LEFT), ISR_JOYSTICK_LEFT, LOW);
  attachInterrupt(digitalPinToInterrupt(JOYSTICK_RIGHT), ISR_JOYSTICK_RIGHT, LOW);
  attachInterrupt(digitalPinToInterrupt(BUTTON_TOP), ISR_BUTTON_TOP, LOW);
  attachInterrupt(digitalPinToInterrupt(BUTTON_MID), ISR_BUTTON_MID, LOW);
  // limitation // attachInterrupt(digitalPinToInterrupt(BUTTON_BOT), ISR_buttonBot, LOW);

  tft.begin();
  tft.setRotation(2);

  rtc.begin();
  DateTime now = DateTime(F(__DATE__), F(__TIME__));
  //!!! notice The year is limited to 2000-2099
  rtc.adjust(now);

  if (DEBUG)
  {
    Serial.begin(9600);
    Serial.println("DEBUG OUTPUT..");
  }

  pageTempHumiSetup();
  pageWordColourMatchGameSetup();
  pageBatterySetup(&tft);
}

// put your main code here, to run repeatedly:
void loop()
{
  updatePageToShow();
  switch (pageToShow)
  {
  case PAGE_HOME:
    pageHomeLoop(&tft);
    break;
  case PAGE_DATE_TIME:
    pageDateTimeLoop(&tft, &rtc);
    break;
  case PAGE_TEMP_HUMI:
    pageTempHumiLoop(&tft);
    break;
  case PAGE_WORD_COLOUR_MATCH_GAME:
    pageWordColourMatchGameLoop(&tft, &rtc);
    break;
  case PAGE_BATTERY:
    pageBatteryLoop(&tft);
    break;
  default:
    break;
  }
}

void updatePageToShow()
{
  if (buttonTopPressed)
  {
    if (pageToShow == 1)
    {
      pageToShow = PAGES_MAX;
    }
    else
    {
      pageToShow -= 1;
    }
    buttonTopPressed = 0;
  }

  if (buttonMidPressed)
  {
    if (pageToShow == PAGES_MAX)
    {
      pageToShow = 1;
    }
    else
    {
      pageToShow += 1;
    }
    buttonMidPressed = 0;
  }

  if (digitalRead(BUTTON_BOT) == LOW)
  {
    pageToShow = PAGE_HOME;
  }
}
