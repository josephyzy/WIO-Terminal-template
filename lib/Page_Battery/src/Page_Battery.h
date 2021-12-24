#ifndef __PAGE_BATTERY__
#define __PAGE_BATTERY__

#include <Arduino.h>

#include "TFT_eSPI.h"
#include "../../../include/Free_Fonts.h"     //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h
#include <SparkFunBQ27441.h>

void pageBatterySetup(TFT_eSPI *tft);
void pageBatteryLoop(TFT_eSPI *tft);
void setupBQ27441(TFT_eSPI *tft);
void printBatteryStats(TFT_eSprite *spr);

#endif