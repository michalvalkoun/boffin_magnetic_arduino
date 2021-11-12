#define LED1 A3
#define LED2 6
#define LED3 7
#define LED4 0

#define BUTTON_PIN 3

void leds(bool led1, bool led2, bool led3, bool led4)
{
    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LED3, led3);
    digitalWrite(LED4, led4);
}
void leds(bool all)
{
    digitalWrite(LED1, all);
    digitalWrite(LED2, all);
    digitalWrite(LED3, all);
    digitalWrite(LED4, all);
}