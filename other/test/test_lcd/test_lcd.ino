#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(4);

void setup()
{
    display.begin(SH1106_SWITCHCAPVCC);
    display.setTextColor(WHITE);
}

void loop()
{
    display.fillRect(0, 0, display.width(), display.height(), 1);
    display.display();
}