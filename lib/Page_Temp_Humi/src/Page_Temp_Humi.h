#ifndef __PAGE_TEMP_HUMI__
#define __PAGE_TEMP_HUMI__

#include "AHT20.h"

#include <Arduino.h>

#include "TFT_eSPI.h"
#include "../../../include/Free_Fonts.h"     //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h

void pageTempHumiSetup();
void pageTempHumiLoop(TFT_eSPI *tft);

#endif