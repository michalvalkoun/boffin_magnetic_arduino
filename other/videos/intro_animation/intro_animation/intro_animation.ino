#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"
#include "display.h"
#include "buttons.h"

const uint8_t *pics[17] = {
    pic1,
    pic2,
    pic3,
    pic4,
    // pic5,
    pic6,
    pic7,
    // pic8,
    // pic9,
    pic10,
    // pic11,
    pic12,
    // pic13,
    pic14,
    // pic15,
    pic16,
    // pic17,
    pic18,
    // pic19,
    pic20,
    // pic21,
    pic22,
    pic23,
    pic24,
    pic25,
    pic26};
int num = 0;
int counter = 0;
void Draw()
{
    switch (game_state)
    {
    case STATE_MENU:
        break;
    case STATE_PLAY:
        if (counter++ % 3 == 0)
            num++;
        if (num < 17)
            display.drawBitmap(0, 0, pics[num], display.width(), display.height(), 1);
        else
            display.fillRect(0, 0, display.width(), display.height(), 1);
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