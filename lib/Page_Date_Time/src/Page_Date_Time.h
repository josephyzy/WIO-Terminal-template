#ifndef __PAGE_DATE_TIME__
#define __PAGE_DATE_TIME__

#include "RTC_SAMD51.h"
#include "TFT_eSPI.h"
#include "../../../include/Free_Fonts.h"     //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h

void pageDateTimeLoop(TFT_eSPI *tft, RTC_SAMD51 *rtc);

#endif