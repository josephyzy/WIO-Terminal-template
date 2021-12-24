#include <Page_Home.h>

#define FONT FMB12 // See "include/Free_Fonts.h" for options

void pageHomeLoop(TFT_eSPI *tft)
{
    TFT_eSprite spr = TFT_eSprite(tft); //Initializing buffer

    spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

    spr.fillSprite(TFT_GREENYELLOW); //Fill background

    spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
    spr.setFreeFont(FMB12);
    //  spr.setTextSize(1);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Home", 5, 6);

    unsigned int rowHeight = 20;
    unsigned int topMargin = 33;
    unsigned int leftMargin = 0;
    for (unsigned int i = 0; i < 13; i++)
    {
        spr.drawString("Ln " + String(i) + " posY = " + String(topMargin + i * rowHeight), leftMargin, topMargin + i * rowHeight);
    }

    spr.drawString("01234567890123456789", leftMargin, 293);

    spr.pushSprite(0, 0); //Push to LCD

    spr.deleteSprite();
}
