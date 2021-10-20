#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"
#include "display.h"
#include "buttons.h"

const uint8_t *pics[5] = {pic1, pic2, pic3, pic4, pic5};
int num = 0;
int counter = 0;
bool turn = true;
void Draw()
{
    switch (game_state)
    {
    case STATE_MENU:
        break;
    case STATE_PLAY:
        counter++;
        if (counter % 3 == 0)
        {
            turn ? num++ : num--;
            if (num <= 0 || num >= 4)
                turn = !turn;
        }

        display.drawBitmap(0, 0, pics[num], display.width(), display.height(), 1);
        break;
    case STATE_GAMEOVER:
        break;
    }
}
void GameStep()
{
    switch (game_state)
    {
    case STATE_MENU:
        break;
    case STATE_GAMEOVER:
        break;
    case STATE_PLAY:
        break;
    }
}
void StartNewGame()
{
    game_state = STATE_PLAY;
}
void setup()
{
    DisplaySetup();
    ButtonsSetup();
    DrawLogo(F("Halloween"), 2000);
    StartNewGame();
}

void loop()
{
    ControlStep();
    GameStep();
    Draw();
    display.display();
    display.clearDisplay();
}