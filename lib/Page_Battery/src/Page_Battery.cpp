#include <Page_Battery.h>

const unsigned int BATTERY_CAPACITY = 650; // Set Wio Terminal Battery's Capacity

void pageBatterySetup(TFT_eSPI *tft)
{
    setupBQ27441(tft);
}

void pageBatteryLoop(TFT_eSPI *tft)
{
    TFT_eSprite spr = TFT_eSprite(tft); //Initializing buffer

    spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

    spr.fillSprite(TFT_GREENYELLOW); //Fill background

    spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
    spr.setFreeFont(FMB12);
    //  spr.setTextSize(1);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Battery Stats", 5, 6);

    spr.setFreeFont(FMB9);
    printBatteryStats(&spr);

    spr.pushSprite(0, 0); //Push to LCD

    spr.deleteSprite();
}

void setupBQ27441(TFT_eSPI *tft)
{
    // Use lipo.begin() to initialize the BQ27441-G1A and confirm that it's
    // connected and communicating.
    if (!lipo.begin()) // begin() will return true if communication is successful
    {
        // If communication fails, print an error message and loop forever.
        Serial.println("Error: Unable to communicate with BQ27441.");
        Serial.println("  Check wiring and try again.");
        Serial.println("  (Battery must be plugged into Battery Babysitter!)");
        tft->setTextColor(TFT_RED);
        tft->setCursor((320 - tft->textWidth("Battery Not Initialised!")) / 2, 120);
        tft->print("Battery Not Initialised!");
        while (1)
            ;
    }
    Serial.println("Connected to BQ27441!");

    // Uset lipo.setCapacity(BATTERY_CAPACITY) to set the design capacity
    // of your battery.
    lipo.setCapacity(BATTERY_CAPACITY);
}

void printBatteryStats(TFT_eSprite *spr)
{
    // Read battery stats from the BQ27441-G1A
    unsigned int soc = lipo.soc();                   // Read state-of-charge (%)
    unsigned int volts = lipo.voltage();             // Read battery voltage (mV)
    int current = lipo.current(AVG);                 // Read average current (mA)
    unsigned int fullCapacity = lipo.capacity(FULL); // Read full capacity (mAh)
    unsigned int capacity = lipo.capacity(REMAIN);   // Read remaining capacity (mAh)
    int power = lipo.power();                        // Read average power draw (mW)
    int health = lipo.soh();                         // Read state-of-health (%)

    // Now print out those values:
    String toPrint = String(soc) + "% | ";
    toPrint += String(volts) + " mV | ";
    toPrint += String(current) + " mA | ";
    toPrint += String(capacity) + " / ";
    toPrint += String(fullCapacity) + " mAh | ";
    toPrint += String(power) + " mW | ";
    toPrint += String(health) + "%";

    spr->fillRect(0, 30, 240, 320, TFT_BLUE);

    // LCD Graphics
    spr->setTextColor(TFT_MAGENTA);
    spr->drawString("Battery Life:", 5, 40);
    spr->drawString("Battery Volt:", 5, 65);
    spr->drawString("Avg Current :", 5, 90);
    spr->drawString("Cap Left    :", 5, 115);
    spr->drawString("Cap Max     :", 5, 140);
    spr->drawString("Avg Power   :", 5, 165);
    spr->drawString("Health      :", 5, 190);

    // Data
    spr->setTextColor(TFT_WHITE);
    spr->drawString(String(soc) + " % ", 150, 40);
    spr->drawString(String(volts) + " mV ", 150, 65);
    spr->drawString(String(current) + " mA ", 150, 90);
    spr->drawString(String(capacity) + " mAh ", 150, 115);
    spr->drawString(String(fullCapacity) + " mAh ", 150, 140);
    spr->drawString(String(power) + " mW ", 150, 165);
    spr->drawString(String(health) + " % ", 150, 190);
    //spr->pushSprite(0, 0);
    //spr.deleteSprite();
}
