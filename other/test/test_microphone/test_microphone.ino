#include <Adafruit_SH1106.h>
Adafruit_SH1106 display(4);
#include "display.h"

#define MIN_VOLTAGE 0.1
#define MAX_VOLTAGE 0.6
#define BAR_TIMER 20
#define SAMPLE_NUM 10
#define REFERENCE_VOLTAGE 5.6

float getVoltage()
{
    uint32_t average = 0;
    for (uint8_t i = 0; i < SAMPLE_NUM; i++)
    {
        average += analogRead(A2);
        delay(5);
    }
    return ((float)average / (float)SAMPLE_NUM * (float)REFERENCE_VOLTAGE) / 1024.0;
}

void setup()
{
    DisplaySetup();
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{
    static float last_voltage = 0;
    static uint8_t timer = 0;
    display.drawRect(0, 0, display.width(), display.height(), 1);

    float voltage = getVoltage();

    if (voltage > last_voltage)
    {
        last_voltage = voltage;
        timer = 0;
    }

    if (timer > BAR_TIMER)
        last_voltage = 0;
    else
        timer++;

    display.fillRect(0, 0, mapfloat(last_voltage, MIN_VOLTAGE, MAX_VOLTAGE, 0, display.width()), 10, 1);
    display.fillRect(0, 0, mapfloat(voltage, MIN_VOLTAGE, MAX_VOLTAGE, 0, display.width()), display.height(), 1);

    if (voltage < MAX_VOLTAGE / 2)
        display.setTextColor(WHITE);
    else
        display.setTextColor(BLACK);
    PrintCenter(String(voltage > MIN_VOLTAGE ? voltage : 0) + String(" V"), 25, 1);

    display.display();
    display.clearDisplay();
}