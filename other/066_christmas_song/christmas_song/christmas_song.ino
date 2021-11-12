#include "config.h"

const Song song(melody1, sizeof(melody1) / sizeof(melody1[0]), TEMPO1);

void button_interupt()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    if (interrupt_time - last_interrupt_time > 200)
    {
        keep_playing = !keep_playing;
        last_interrupt_time = interrupt_time;
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_interupt, FALLING);
}

void loop()
{
    song.play();
}
