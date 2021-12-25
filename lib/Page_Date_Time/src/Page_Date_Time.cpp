#include <Page_Date_Time.h>

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void pageDateTimeLoop(TFT_eSPI *tft, RTC_SAMD51 *rtc)
{
    TFT_eSprite spr = TFT_eSprite(tft); //Initializing buffer
    String dateStr, dayStr, timeStr;
    DateTime now = rtc->now();

    spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

    spr.fillSprite(TFT_YELLOW); //Fill background

    spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
    spr.setFreeFont(FMB12);
    //  spr.setTextSize(1);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Date Time", 5, 6);

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
    spr.setTextDatum(MC_DATUM);
    spr.drawString(dateStr, 120, 100);
    spr.drawString(dayStr, 120, 150);
    spr.drawString(timeStr, 120, 200);

    // Set back to default font
    spr.setFreeFont(FMB12);

    // Push to LCD
    spr.pushSprite(0, 0); //Push to LCD

    spr.deleteSprite();
}