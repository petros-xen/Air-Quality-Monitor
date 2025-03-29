// AirQualityManager.h
#ifndef AIR_QUALITY_MANAGER_H
#define AIR_QUALITY_MANAGER_H

#include "AHT20_BMP280.h"
#include "PM25_Sensor.h"
#include "Photoresistor.h"
#include <Adafruit_Sensor.h>
#include <Arduino.h>

struct AirQualityData
{
    float temperature = NAN;
    float humidity = NAN;
    float pressure = NAN;
    float pm25 = -1;
    int lightLevel = 0;

    bool tempValid = false;
    bool humidityValid = false;
    bool pressureValid = false;
    bool pmValid = false;

    String qualityLabel = "Unknown";

    // ✅ Add these lines:
    int r = 255;
    int g = 255;
    int b = 255;
};

class AirQualityManager
{
public:
    AirQualityManager(AHT20_BMP280 *sensor, PM25_Sensor *pmSensor, Photoresistor *lightSensor);
    void update();
    AirQualityData getData() const;

private:
    AHT20_BMP280 *_sensor;
    PM25_Sensor *_pmSensor;
    Photoresistor *_lightSensor;
    AirQualityData _data;

    void classifyAirQuality();
};

#endif