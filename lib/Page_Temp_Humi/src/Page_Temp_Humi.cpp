#include <Page_Temp_Humi.h>

#define FONT FMB12 // See "include/Free_Fonts.h" for options

AHT20 AHT; // Temperature and humidity sensor

void pageTempHumiSetup()
{
    AHT.begin();
}

void pageTempHumiLoop(TFT_eSPI *tft)
{
    TFT_eSprite spr = TFT_eSprite(tft); //Initializing buffer

    spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

    spr.fillSprite(TFT_GREENYELLOW); //Fill background

    spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
    spr.setFreeFont(FMB12);
    //  spr.setTextSize(1);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Temp Humi", 5, 6);

    float humi, temp;

    int ret = AHT.getSensor(&humi, &temp);
    if (ret)
    { // GET DATA OK

        //Setting temperature
        spr.setFreeFont(FMB18);
        spr.setTextDatum(MC_DATUM);
        spr.drawString("Temperature", 120, 85);
        spr.setFreeFont(FMB24);
        spr.setTextDatum(MR_DATUM);
        spr.drawFloat(temp, 1, 160, 120);
        spr.setTextDatum(ML_DATUM);
        spr.drawString("C", 160, 120);

        //Setting humidity
        spr.setFreeFont(FMB18);
        spr.setTextDatum(MC_DATUM);
        spr.drawString("Humidity", 120, 205);
        spr.setFreeFont(FMB24);
        spr.setTextDatum(MR_DATUM);
        spr.drawNumber(humi * 100, 100, 240); //Display humidity values
        spr.setTextDatum(ML_DATUM);
        spr.drawString("%RH", 100, 240);
    }
    else
    { // GET DATA FAIL
    }

    spr.pushSprite(0, 0); //Push to LCD

    spr.deleteSprite();
}
