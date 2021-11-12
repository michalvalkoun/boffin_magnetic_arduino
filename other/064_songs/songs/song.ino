#include "config.h"

#define SONG_SIZE 11
const Song songs[SONG_SIZE] = {
    {melody1, sizeof(melody1) / sizeof(melody1[0]), TEMPO1},
    {melody2, sizeof(melody2) / sizeof(melody2[0]), TEMPO2},
    {melody3, sizeof(melody3) / sizeof(melody3[0]), TEMPO3},
    {melody4, sizeof(melody4) / sizeof(melody4[0]), TEMPO4},
    {melody5, sizeof(melody5) / sizeof(melody5[0]), TEMPO5},
    {melody6, sizeof(melody6) / sizeof(melody6[0]), TEMPO6},
    {melody7, sizeof(melody7) / sizeof(melody7[0]), TEMPO7},
    {melody8, sizeof(melody8) / sizeof(melody8[0]), TEMPO8},
    {melody9, sizeof(melody9) / sizeof(melody9[0]), TEMPO9},
    {melody10, sizeof(melody10) / sizeof(melody10[0]), TEMPO10},
    {melody11, sizeof(melody11) / sizeof(melody11[0]), TEMPO11},
};

int cur_song = 0;
bool keep_playing = true;

void button_interupt()
{
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    if (interrupt_time - last_interrupt_time > 200)
    {
        if (keep_playing)
            button_state = true;
        keep_playing = true;
        if (++cur_song >= SONG_SIZE)
            cur_song = 0;
        Serial.print("Interupt: ");
        Serial.println(cur_song + 1);

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

    if (keep_playing)
        keep_playing = songs[cur_song].play();
}
