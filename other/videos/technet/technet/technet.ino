#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"
#include "display.h"
#include "buttons.h"

uint8_t cur_q;

uint8_t score;
uint8_t game_timer;
uint8_t gameover_timer;
bool wrong_type;

void DrawBackground()
{
    display.drawRect(10, 35, 108, 6, 1);

    display.setCursor(0, 49);
    display.setTextSize(2);
    display.println(F("YES"));

    display.setCursor(104, 49);
    display.setTextSize(2);
    display.println(F("NO"));

    PrintCenter(score, 49, 2);
}

void PickStr(uint8_t i)
{
    display.setTextSize(1);
    display.setCursor(0, 0);
    switch (i)
    {
    case 0:
        display.println(F("Je Vaclav Nyvlt nejlepsim redaktorem?"));
        break;
    case 1:
        display.println(F("Portal idnes.cz byl zalozen v roce 1998."));
        break;
    case 2:
        display.println(F("Je majitelem portalu Idnes.cz Jara Cimrman?"));
        break;
    case 3:
        display.println(F("Skupina The Doors je nejlepsi kapela na svete?"));
        break;
    case 4:
        display.println(F("Je Diana Krall nejlepsi Jazz zpevackou?"));
        break;
    case 5:
        display.println(F("K poslechu hudby staci mobilni telefon."));
        break;
    case 6:
        display.println(F("Byl rok 2006 zlomovy pro Technet.cz?"));
        break;
    case 7:
        display.println(F("Je Boffin Magnetic nejlepsi stavebnici na svete?"));
        break;
    }
}
bool PickRes(uint8_t i)
{
    switch (i)
    {
    case 0:
        return true;
        break;
    case 1:
        return true;
        break;
    case 2:
        return false;
        break;
    case 3:
        return true;
        break;
    case 4:
        return true;
        break;
    case 5:
        return false;
        break;
    case 6:
        return true;
        break;
    case 7:
        return true;
        break;
    }
}

void Draw()
{
    switch (game_state)
    {
    case STATE_PLAY:
        DrawBackground();
        PickStr(cur_q);
        display.fillRect(10, 35, game_timer, 6, 1);
        break;
    case STATE_WIN:
        PrintCenter("You Win", 10, 2);
        PrintCenter("Score", 40, 1);
        PrintCenter(score, 50, 1);
        break;
    case STATE_GAMEOVER:
        if (gameover_timer < 50)
        {
            DrawBackground();
            gameover_timer++;
            if (wrong_type)
            {
                display.fillRect(10, 35, game_timer, 6, 1);
                if (gameover_timer % 10 < 5)
                    PickStr(cur_q);
            }
            else
            {
                PickStr(cur_q);
                if (gameover_timer % 10 < 5)
                    display.fillRect(10, 35, game_timer, 6, 1);
            }
        }
        else
        {
            PrintCenter("Game Over", 10, 2);
            PrintCenter("Score", 40, 1);
            PrintCenter(score, 50, 1);
        }
        break;
    }
}

void GameStep()
{
    switch (game_state)
    {
    case STATE_GAMEOVER:
        if (key_code & (KEY_A | KEY_B))
            StartNewGame();
        break;
    case STATE_WIN:
        if (key_code & (KEY_A | KEY_B))
            StartNewGame();
        break;
    case STATE_PLAY:
        game_timer--;
        if (cur_q > 7)
            game_state = STATE_WIN;
        if (game_timer <= 0)
        {
            game_state = STATE_GAMEOVER;
            wrong_type = false;
        }
        if ((key_code & KEY_A && PickRes(cur_q)) || (key_code & KEY_B && !PickRes(cur_q)))
        {
            score++;
            game_timer = 108;
            cur_q++;
        }
        else if ((key_code & KEY_A && !PickRes(cur_q)) || (key_code & KEY_B && PickRes(cur_q)))
        {
            game_state = STATE_GAMEOVER;
            wrong_type = true;
        }
    }
}

void StartNewGame()
{
    game_state = STATE_PLAY;
    randomSeed(analogRead(0));
    game_timer = 108;
    score = 0;
    gameover_timer = 0;
    cur_q = 0;
}

void setup()
{
    DisplaySetup();
    ButtonsSetup();
    DrawLogo(F("Technet"), 2000);
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