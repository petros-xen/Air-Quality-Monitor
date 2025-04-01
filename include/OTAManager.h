#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <ArduinoOTA.h>

class OTAManager
{
public:
    static void begin(const char *hostname);
    static void handle();
};

#endif