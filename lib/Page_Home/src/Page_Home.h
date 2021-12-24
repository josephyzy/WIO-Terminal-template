#ifndef __PAGE_HOME__
#define __PAGE_HOME__

#include "RTC_SAMD51.h"

#include <Arduino.h>

#include "TFT_eSPI.h"
#include "../../../include/Free_Fonts.h"     //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h

void pageHomeLoop(TFT_eSPI *tft);

#endif