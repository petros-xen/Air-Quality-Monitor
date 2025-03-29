#include "RGB_LED.h"

RGB_LED::RGB_LED(int redPin, int greenPin, int bluePin)
    : _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin),
      _redValue(0), _greenValue(0), _blueValue(0) {}

void RGB_LED::begin()
{
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
}

void RGB_LED::setColor(int red, int green, int blue)
{
    _redValue = red;
    _greenValue = green;
    _blueValue = blue;
    analogWrite(_redPin, (red * _brightness) / 255);
    analogWrite(_greenPin, (green * _brightness) / 255);
    analogWrite(_bluePin, (blue * _brightness) / 255);
}

void RGB_LED::setBrightnessFromLight(int lightLevel)
{
    if (lightLevel < 150)
    {
        _brightness = 0;
    }
    else
    {
        _brightness = map(lightLevel, 150, 1023, 50, 255);
    }

    // Reapply the current color with the new brightness
    setColor(_redValue, _greenValue, _blueValue);
}