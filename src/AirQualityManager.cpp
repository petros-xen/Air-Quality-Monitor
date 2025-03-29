#include "AirQualityManager.h"

AirQualityManager::AirQualityManager(AHT20_BMP280 *sensor, PM25_Sensor *pmSensor, Photoresistor *lightSensor)
    : _sensor(sensor), _pmSensor(pmSensor), _lightSensor(lightSensor)
{
}

void AirQualityManager::update()
{
    sensors_event_t humidityEvent, tempEvent;
    _sensor->readAHT(&humidityEvent, &tempEvent);

    _data.temperature = tempEvent.temperature;
    _data.humidity = humidityEvent.relative_humidity;
    _data.pressure = _sensor->getPressure();
    _data.lightLevel = _lightSensor->readLight();

    if (_pmSensor->isConnected())
    {
        _data.pm25 = _pmSensor->readPM25();
        _data.pmValid = (_data.pm25 >= 0);
    }
    else
    {
        _data.pm25 = -1;
        _data.pmValid = false;
    }

    _data.tempValid = !(isnan(_data.temperature) || _data.temperature < -20 || _data.temperature > 100);
    _data.humidityValid = !(isnan(_data.humidity) || _data.humidity < 0 || _data.humidity > 100);
    _data.pressureValid = !(isnan(_data.pressure) || _data.pressure < 800 || _data.pressure > 1200);

    classifyAirQuality();
}

void AirQualityManager::classifyAirQuality()
{
    if (!_data.pmValid)
    {
        _data.qualityLabel = "Sensor Error";
    }
    else if (_data.pm25 < 15)
    {
        _data.qualityLabel = "Good";
    }
    else if (_data.pm25 < 35)
    {
        _data.qualityLabel = "Moderate";
    }
    else
    {
        _data.qualityLabel = "Poor";
    }
}

AirQualityData AirQualityManager::getData() const
{
    return _data;
}