#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"
#include "display.h"
#include "buttons.h"

#define MAZE_WIDTH 15
#define MAZE_HEIGHT 31
uint16_t maze[] = {
    0b1101111111111111,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1101010101010101,
    0b1100000000000001,
    0b1111111111111101,
    0b1100000000000101, //exit
    0b0000000000000000};

#define CELL_WIDTH display.width() / MAZE_WIDTH
#define CELL_HEIGHT display.height() / MAZE_HEIGHT

Player player(1, 1);

bool readPixel(uint8_t i, uint8_t j)
{
    uint16_t Data = maze[i];
    byte Hi = (Data & 0xFF00) >> 8;
    byte Lo = Data & 0x00FF;
    if (j > 7)
        return bitRead(Lo, 7 - (j % 8));
    else
        return bitRead(Hi, 7 - (j % 8));
}

void Draw()
{
    switch (game_state)
    {
    case STATE_MENU:
        break;
    case STATE_PLAY:
        display.fillCircle(player.x * CELL_WIDTH + CELL_WIDTH / 2, player.y * CELL_HEIGHT + CELL_HEIGHT / 2, CELL_HEIGHT / 2 - 1, 1);
        // for (uint8_t i = 0; i < MAZE_WIDTH; i++)
        //     for (uint8_t j = 0; j < MAZE_HEIGHT; j++)
        //         if (maze[i][j])
        //             display.fillRect(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, 1);
        for (uint8_t i = 0; i <= MAZE_WIDTH; i++)
            for (uint8_t j = 0; j <= MAZE_HEIGHT; j++)
            {
                if (readPixel(i, j))
                    display.fillRect(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, 1);

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
            if (dir & LEFT)
                player.x--;
            else if (dir & RIGHT)
                player.x++;
            if (dir & UP)
                player.y--;
            else if (dir & DOWN)
                player.y++;

            if (player.x < 0)
                player.x = 0;
            else if (player.x > MAZE_WIDTH - 1)
                player.x = MAZE_WIDTH - 1;
            if (player.y < 0)
                player.y = 0;
            else if (player.y > MAZE_HEIGHT - 1)
                player.y = MAZE_HEIGHT - 1;

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
        DrawLogo(F("Maze"), 2000);
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