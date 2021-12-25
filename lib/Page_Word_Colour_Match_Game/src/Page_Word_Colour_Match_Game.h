#ifndef __PAGE_WORD_COLOUR_MATCH_GAME__
#define __PAGE_WORD_COLOUR_MATCH_GAME__

#include "RTC_SAMD51.h"

#include <Arduino.h>

#include "TFT_eSPI.h"
#include "../../../include/Free_Fonts.h"     //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h

extern volatile int joystickPressPressed;

void pageWordColourMatchGameSetup();
void pageWordColourMatchGameLoop(TFT_eSPI *tft, RTC_SAMD51 *rtc);

void updateScoreAndLife(TFT_eSPI *tft);
void updateScreenFirstBoot(TFT_eSPI *tft);
void updateScreenPlaying(TFT_eSPI *tft);
void updateScreenGameOver(TFT_eSPI *tft);

#endif