#ifndef PM25_SENSOR_H
#define PM25_SENSOR_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class PM25_Sensor
{
public:
    PM25_Sensor(uint8_t rxPin, uint8_t txPin);
    bool begin();
    float readPM25();
    bool isConnected() const;

private:
    SoftwareSerial _serial;
    bool _connected;
};

#endif