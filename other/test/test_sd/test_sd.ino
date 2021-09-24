#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
    pinMode(5, OUTPUT);
    pinMode(8, OUTPUT);

    Serial.begin(9600);
    while (!Serial)
        ;

    if (!SD.begin(10))
        while (1)
            ;

    myFile = SD.open("test.txt", FILE_WRITE);

    if (myFile)
    {
        myFile.println("testing 1, 2, 3.");
        myFile.close();
    }
    else
    {
        while (1)
            ;
    }
    myFile = SD.open("test.txt");
    if (myFile)
    {
        while (myFile.available())
            Serial.write(myFile.read());
        myFile.close();
    }
    else
    {
        while (1)
            ;
    }
    SD.remove("test.txt");
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
}

void loop()
{
}
