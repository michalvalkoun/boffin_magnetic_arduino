#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

#include "config.h"

#define SW1 5
#define SW2 6
#define SW3 7
#define SW4 8

uint8_t timer = 1, frame_delay_timer = 0, frame_delay = 50;
uint16_t frame_speed = 200;

struct Object
{
    uint8_t x, y, w, h;
    Object(uint8_t x, uint8_t y, uint8_t w, uint8_t h) : x(x), y(y), w(w), h(h) {}
};
Object frame((display.width() - 74) / 2, 0, 74, display.height());

void setup()
{
    display.begin(SH1106_SWITCHCAPVCC); // initialize with the I2C addr 0x3D (for the 128x64)
    display.clearDisplay();
    display.setRotation(2);
    display.setTextColor(WHITE);
    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(SW3, INPUT_PULLUP);
    pinMode(SW4, INPUT_PULLUP);
}

void loop()
{
    switch (timer)
    {
    case 1:
        display.drawBitmap(frame.x, frame.y, frame1, frame.w, frame.h, 1);
        break;
    case 2:
        display.drawBitmap(frame.x, frame.y, frame2, frame.w, frame.h, 1);
        break;
    case 3:
        display.drawBitmap(frame.x, frame.y, frame3, frame.w, frame.h, 1);
        break;
    case 4:
        display.drawBitmap(frame.x, frame.y, frame4, frame.w, frame.h, 1);
        break;
    case 5:
        display.drawBitmap(frame.x, frame.y, frame5, frame.w, frame.h, 1);
        break;
    case 6:
        display.drawBitmap(frame.x, frame.y, frame6, frame.w, frame.h, 1);
        break;
    case 7:
        display.drawBitmap(frame.x, frame.y, frame7, frame.w, frame.h, 1);
        break;
    default:
        timer = 1;
        break;
    }
    display.setCursor(0, 0);
    if (!digitalRead(SW1))
        display.println(frame_speed);

    display.display();
    display.clearDisplay();

    if (!digitalRead(SW2))
    {
        if (frame_speed > 0)
            frame_speed -= 10;
    }

    if (!digitalRead(SW3))
        frame_speed += 10;

    if (!digitalRead(SW4))
        frame_delay_timer = frame_delay;

    if (timer == 1 || timer == 7)
    {
        frame_delay_timer++;
        if (frame_delay_timer >= frame_delay)
        {
            timer++;
            frame_delay_timer = 0;
        }
    }
    else
    {
        timer++;
    }
    delay(frame_speed);
}