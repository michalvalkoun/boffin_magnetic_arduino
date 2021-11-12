#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"
#include "display.h"
#include "buttons.h"

#define KEYWORD_LEN 5
char keyword[KEYWORD_LEN];
int still_solving = 0;
bool unlock_state = false;
bool lock_open = false;
void Draw()
{
    switch (game_state)
    {
    case STATE_MENU:
        break;
    case STATE_PLAY:
        if (unlock_state)
            display.drawBitmap(42, 0, lock_open ? unlock : lock, 45, 64, 1);
        else
            for (int i = 0; i < KEYWORD_LEN; i++)
            {
                if (i < still_solving)
                    display.drawLine(11 + i * 23, 40, 22 + i * 23, 40, 1);
                display.setCursor(12 + i * 23, 25);
                display.setTextSize(2);
                display.print(keyword[i]);
            }
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
        if (!unlock_state)
        {
            for (int i = still_solving; i < KEYWORD_LEN; i++)
                keyword[i] = random(33, 126);
            if (key_code & KEY_A)
                if (++still_solving > KEYWORD_LEN)
                    unlock_state = true;
        }
        else if (key_code & KEY_A)
        {
            if (lock_open == true)
            {
                unlock_state = lock_open = false;
                still_solving = 0;
            }
            else
            {
                lock_open = true;
            }
        }

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