#ifndef RGB_LED_H
#define RGB_LED_H

#include <Arduino.h>

class RGB_LED
{
public:
    RGB_LED(int redPin, int greenPin, int bluePin);
    void begin();
    void setColor(int red, int green, int blue);
    void setBrightnessFromLight(int lightLevel);

private:
    int _redPin, _greenPin, _bluePin;
    int _redValue, _greenValue, _blueValue;
    int _brightness = 255;
};

#endif