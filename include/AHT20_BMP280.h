#ifndef AHT20_BMP280_H
#define AHT20_BMP280_H

#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

class AHT20_BMP280
{
public:
    bool begin(TwoWire *customWire);
    void readAHT(sensors_event_t *humidity, sensors_event_t *temp);
    float getPressure();

private:
    TwoWire *_wire;
    Adafruit_AHTX0 aht;
    Adafruit_BMP280 bmp;
};

#endif