#include <Adafruit_NeoPixel.h>

#define PIN 6 // input pin Neopixel is attached to

#define NUMPIXELS 32 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
    pixels.begin();

    pixels.show();
}

int prevTime = 0;

int redButton = 0;
int blueButton = 0;
bool blue = true;

int position = 0;

void egenDelay(int hvor_lenge)
{
    prevTime = millis();
    while (millis() - prevTime < hvor_lenge)
    {
        // sjekker om knapper har blitt trykket på
        updateKnapp();
        delay(50); // litt delay for å ikke overjobbe den
    }
}

void updateKnapp()
{

    // endrer modus
    if (redButton != digitalRead(3))
    {
        redButton = digitalRead(3);
        if (redButton)
        {
            Serial.println("red");
            if (position > 26){
            push(false);
            }
        }
    }
    if (blueButton != digitalRead(2))
    {
        blueButton = digitalRead(2);
        if (blueButton)
        {
   
            Serial.println("blue");
            if (position < 5){
            push(true);
            }
        }
    }
}

void push(bool i)
{
    if (i)
    {
        blue = true;
    }
    else
    {
        blue = false;
    }
}

void loop()
{
    // make a pixel go back and forth
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(position+1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(position-1, pixels.Color(0, 0, 0));
        for (int i = 0; i < 5; i++)
        {
            pixels.setPixelColor(i, pixels.Color(0, 0, 255));
            pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(255, 0, 0));
        }
        pixels.setPixelColor(position, pixels.Color(0, 255, 0));
        pixels.show();
        egenDelay(100);
        if (blue)
        {
            position++;
        }
        else
        {
            position--;
        }
    }
}