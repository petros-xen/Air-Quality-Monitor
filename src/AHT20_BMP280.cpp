#include "AHT20_BMP280.h"

bool AHT20_BMP280::begin(TwoWire *customWire)
{
    bool ahtOk = aht.begin(customWire);

    bool bmpOk = bmp.begin(0x76);
    if (!bmpOk)
        bmpOk = bmp.begin(0x77);

    return ahtOk || bmpOk;
}

void AHT20_BMP280::readAHT(sensors_event_t *humidity, sensors_event_t *temp)
{
    aht.getEvent(humidity, temp);
}

float AHT20_BMP280::getPressure()
{
    return bmp.readPressure() / 100.0F;
}