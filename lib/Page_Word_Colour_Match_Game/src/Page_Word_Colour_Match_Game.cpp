#include <Page_Word_Colour_Match_Game.h>

#define FONT FMB12 // See "include/Free_Fonts.h" for options

#define MAX_COLOURS 5
unsigned int colourBackground[MAX_COLOURS] = {TFT_RED, TFT_GREEN, TFT_YELLOW, TFT_WHITE, TFT_BLUE};
String colourWord[MAX_COLOURS] = {"RED", "GREEN", "YELLOW", "WHITE", "BLUE"};
unsigned int colourBackgroundIndex = 0;
unsigned int colourWordIndex = 1;
String headerFooter[2] = {"XXXXXXXX", "++++++++"};
unsigned int headerFooterIndex = 0;

#define LIVES_START_VALUE 3
unsigned int lives = LIVES_START_VALUE;
unsigned int score = 0;
unsigned int gameOver = 0;
unsigned int firstBoot = 1;
unsigned int previousUpdateSecondsTime = 0;

void pageWordColourMatchGameSetup()
{
    // if analog input pin 0 is unconnected, random analog
    // noise will cause the call to randomSeed() to generate
    // different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(0));
}

void pageWordColourMatchGameLoop(TFT_eSPI *tft, RTC_SAMD51 *rtc)
{
    if (firstBoot)
    {
        updateScreenFirstBoot(tft);

        // Wait till joystick pressed
        while (joystickPressPressed == 0)
        {
        }

        // Initialize variables
        joystickPressPressed = 0;
        firstBoot = 0;
        previousUpdateSecondsTime = rtc->now().secondstime();
    }

    if (rtc->now().secondstime() - previousUpdateSecondsTime > 0) // Execute every 1 second
    {
        if (gameOver)
        {
            updateScreenGameOver(tft);
            if (joystickPressPressed == 1) // Restart game
            {
                score = 0;
                lives = LIVES_START_VALUE;
                gameOver = 0;

                // Set index to different initial values
                colourBackgroundIndex = 0;
                colourWordIndex = 1;

                joystickPressPressed = 0;
            }
        }
        else
        {
            updateScoreAndLife(tft);
            if (gameOver != 1)
            {
                updateScreenPlaying(tft);
            }
        }
        previousUpdateSecondsTime = rtc->now().secondstime();
    }
}

void updateScoreAndLife(TFT_eSPI *tft)
{
    if (colourBackgroundIndex == colourWordIndex)
    {
        if (joystickPressPressed == 1)
        {
            score += 1;
            joystickPressPressed = 0;
        }
        else
        {
            lives -= 1;
            if (lives == 0)
            {
                gameOver = 1;
            }
        }
    }
    else
    {
        if (joystickPressPressed == 1)
        {
            lives -= 1;
            if (lives == 0)
            {
                gameOver = 1;
            }
            joystickPressPressed = 0;
        }
    }
}

void updateScreenFirstBoot(TFT_eSPI *tft)
{
    TFT_eSprite spr = TFT_eSprite(tft); //Initializing buffer

    spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

    spr.fillSprite(TFT_CYAN);

    spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
    spr.setFreeFont(FMB12);
    //  spr.setTextSize(1);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Word Colour Match", 1, 6);

    spr.setTextDatum(MC_DATUM);
    spr.setFreeFont(FMB18);
    spr.setTextColor(TFT_BLACK);

    spr.drawString("Press", 120, 50);
    spr.drawString("joystick", 120, 90);
    spr.drawString("when", 120, 130);
    spr.drawString("word", 120, 170);
    spr.drawString("and", 120, 210);
    spr.drawString("colour", 120, 250);
    spr.drawString("matches", 120, 290);

    spr.pushSprite(0, 0); // Push to LCD

    spr.deleteSprite();
}

void updateScreenPlaying(TFT_eSPI *tft)
{
    TFT_eSprite spr = TFT_eSprite(tft); //Initializing buffer

    spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

    colourBackgroundIndex = rand() % MAX_COLOURS;
    spr.fillSprite(colourBackground[colourBackgroundIndex]);

    spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
    spr.setFreeFont(FMB12);
    //  spr.setTextSize(1);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Word Colour Match", 1, 6);

    spr.setTextDatum(TL_DATUM);
    spr.setFreeFont(FMB18);
    spr.setTextColor(TFT_BLACK);
    String scoreText = "Score:";
    scoreText = scoreText + String(score);
    spr.drawString(scoreText, 0, 30);
    String livesText = "Lives:";
    livesText = livesText + String(lives);
    spr.drawString(livesText, 0, 60);

    spr.setTextDatum(MC_DATUM);
    spr.setFreeFont(FMB24);
    spr.setTextColor(TFT_BLACK);

    spr.drawString(headerFooter[headerFooterIndex], 120, 110);
    spr.drawString(headerFooter[headerFooterIndex], 120, 250);

    colourWordIndex = rand() % MAX_COLOURS;
    spr.drawString(colourWord[colourWordIndex], 120, 180);

    spr.pushSprite(0, 0); // Push to LCD
    spr.deleteSprite();

    headerFooterIndex = (headerFooterIndex + 1) % 2;
}

void updateScreenGameOver(TFT_eSPI *tft)
{
    TFT_eSprite spr = TFT_eSprite(tft); //Initializing buffer

    spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

    spr.fillSprite(colourBackground[colourBackgroundIndex]);

    spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
    spr.setFreeFont(FMB12);
    //  spr.setTextSize(1);
    spr.setTextColor(TFT_BLACK);
    spr.drawString("Word Colour Match", 1, 6);

    spr.setTextDatum(TL_DATUM);
    spr.setFreeFont(FMB18);
    spr.setTextColor(TFT_BLACK);
    String scoreText = "Score:";
    scoreText = scoreText + String(score);
    spr.drawString(scoreText, 0, 30);
    String livesText = "Lives:";
    livesText = livesText + String(lives);
    spr.drawString(livesText, 0, 60);

    spr.setTextDatum(MC_DATUM);
    spr.setFreeFont(FMB24);
    spr.setTextColor(TFT_BLACK);

    spr.drawString(headerFooter[headerFooterIndex], 120, 110);
    spr.drawString(headerFooter[headerFooterIndex], 120, 250);

    spr.drawString("GAME", 120, 160);
    spr.drawString("OVER", 120, 200);

    spr.setFreeFont(FMB9);
    spr.drawString("Press joystick", 120, 280);
    spr.drawString("to try again", 120, 300);

    spr.pushSprite(0, 0); // Push to LCD
    spr.deleteSprite();
}