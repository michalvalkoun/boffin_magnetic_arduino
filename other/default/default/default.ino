#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"
#include "display.h"
#include "buttons.h"

void Draw()
{
    switch (game_state)
    {
    case STATE_MENU:
        break;
    case STATE_PLAY:
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
    DrawLogo(F(""), 2000);
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