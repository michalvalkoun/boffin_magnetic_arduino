#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "display.h"
#include "buttons.h"

#define year 2021
int8_t menu_select;
int8_t menu;

void Draw()
{
    switch (game_state)
    {
    case STATE_PLAY:
        switch (menu)
        {
        case 0:
            display.fillRect(0, 0, 10, display.height(), 1);
            display.fillRect(display.width() - 10, 0, 10, display.height(), 1);

            PrintCenter("PAST", 8, 2);
            PrintCenter("FUTURE", 40, 2);

            display.drawRect(9, 4 + menu_select * 32, display.width() - 10, 22, 1);
            break;
        case 1:
            PrintCenter(F("TRAVEL TO"), 0, 2);
            PrintCenter(year - menu_select, 20, 2);

            display.drawRect(14, 45, 100, 10, 1);
            display.fillRect(14, 45, 100 - menu_select, 10, 1);
            break;
        case 2:
            display.invertDisplay(menu_select++ % 2);
            break;
        }
    }
}

void GameStep()
{
    switch (game_state)
    {
    case STATE_PLAY:
        switch (menu)
        {
        case 0:
            if (dir & DOWN)
                menu_select++;
            else if (dir & UP)
                menu_select--;
            if (menu_select > 1)
                menu_select = 1;
            else if (menu_select < 0)
                menu_select = 0;

            if (key_code & (KEY_A | KEY_J))
            {
                menu_select = 0;
                menu = 1;
            }
            break;
        case 1:
            if (dir & LEFT)
                menu_select++;
            else if (dir & RIGHT)
                menu_select--;
            if (menu_select > 100)
                menu_select = 100;
            else if (menu_select < 0)
                menu_select = 0;

            if (key_code & (KEY_A | KEY_J))
            {
                menu_select = 0;
                menu = 2;
            }
            break;
        case 2:
            if (key_code & (KEY_A | KEY_J))
            {
                display.invertDisplay(false);
                StartNewGame();
            }
            break;
        }
    }
}

void StartNewGame()
{
    game_state = STATE_PLAY;
    menu_select = 0;
    menu = 0;
}

void setup()
{
    DisplaySetup();
    ButtonsSetup();
    DrawLogo("Time Machine", 2000);
    StartNewGame();
}

void loop()
{
    ControlStep(5, 0);
    GameStep();
    Draw();
    display.display();
    display.clearDisplay();
}