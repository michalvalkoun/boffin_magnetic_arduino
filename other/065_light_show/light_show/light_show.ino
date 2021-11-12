#include "config.h"

#define MODE_MAX 4
int mode = 0;

void button_interupt()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    if (interrupt_time - last_interrupt_time > 200)
    {
        if (++mode >= MODE_MAX)
            mode = 0;
        last_interrupt_time = interrupt_time;
    }
}

void setup()
{
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_interupt, FALLING);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    leds(1);
}
void mode0(int time)
{
    leds(1, 0, 0, 0);
    delay(time);
    leds(0, 1, 0, 0);
    delay(time);
    leds(0, 0, 1, 0);
    delay(time);
    leds(0, 0, 0, 1);
    delay(time);
    leds(0, 0, 1, 0);
    delay(time);
    leds(0, 1, 0, 0);
    delay(time);
}

void mode1(int time)
{
    leds(1, 0, 0, 1);
    delay(time);
    leds(0, 1, 1, 0);
    delay(time);
}
void mode2(int time)
{
    leds(1, 1, 0, 0);
    delay(time);
    leds(0, 1, 1, 0);
    delay(time);
    leds(0, 0, 1, 1);
    delay(time);
    leds(1, 0, 0, 1);
    delay(time);
}
void mode3(int time)
{
    leds(1, 1, 0, 0);
    delay(time);
    leds(0, 0, 1, 1);
    delay(time);
}
void loop()
{
    switch (mode)
    {
    case 0:
        mode0(300);
        break;
    case 1:
        mode1(500);
        break;
    case 2:
        mode2(300);
        break;
    case 3:
        mode3(500);
        break;
    }
}