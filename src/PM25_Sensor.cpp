// PM25_Sensor.cpp
#include "PM25_Sensor.h"

PM25_Sensor::PM25_Sensor(uint8_t rxPin, uint8_t txPin)
    : _serial(rxPin, txPin), _connected(false) {}

bool PM25_Sensor::begin()
{
    _serial.begin(9600);
    delay(100);
    // Try a simple communication test
    _serial.listen();
    unsigned long start = millis();
    while (millis() - start < 1000)
    {
        if (_serial.available())
        {
            _connected = true;
            break;
        }
    }
    return _connected;
}

float PM25_Sensor::readPM25()
{
    if (!_connected)
        return -1;

    uint8_t buffer[32];
    if (_serial.available() >= 32)
    {
        _serial.readBytes(buffer, 32);
        if (buffer[0] == 0x42 && buffer[1] == 0x4D)
        {
            uint16_t pm25 = buffer[10] << 8 | buffer[11];
            return static_cast<float>(pm25);
        }
    }
    return -1;
}

bool PM25_Sensor::isConnected() const
{
    return _connected;
}
