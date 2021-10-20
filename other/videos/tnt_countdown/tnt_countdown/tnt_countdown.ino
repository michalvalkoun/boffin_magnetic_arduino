#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"
#include "display.h"
#include "buttons.h"

int8_t counter = 10;
uint8_t timer = 0;
bool countdown = false;
void Draw()
{
    switch (game_state)
    {
    case STATE_MENU:
        break;
    case STATE_PLAY:
        if (counter < 0)
        {
            if (timer++ % 3 == 0)
                display.fillRect(0, 0, display.width(), display.height(), 1);
        }
        else
        {
            display.drawBitmap(0, 0, tnt, display.width(), display.height(), 1);
            if (counter >= 10)
                display.setCursor(56, 25);
            else
                display.setCursor(63, 25);
            display.setTextSize(2);
            display.println(counter);
            if (countdown)
                if (timer++ % 15 == 0)
                    counter--;
        }
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
        if (key_code & KEY_A)
            countdown = true;
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