#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class OLED_Display
{
public:
    OLED_Display(uint8_t width, uint8_t height, TwoWire *wire, int8_t reset);
    void begin(uint8_t address = 0x3C);
    void showBootMessage();
    void showSensorData(float temp, bool tempOk,
                        float hum, bool humOk,
                        float pressure, bool pressureOk,
                        const String &airQualityLabel,
                        float pm25,
                        const String &timestamp);
    void showLoadingAnimation(const String &message, int steps = 10, int delayMs = 150);

private:
    Adafruit_SSD1306 _display;
};

#endif