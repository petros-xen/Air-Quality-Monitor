#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <ArduinoOTA.h>
#include "OLED_Display.h"

class OTAManager
{
public:
    static void begin(OLED_Display *display, const char *hostname = "ESP8266");
    static void handle();

private:
    static OLED_Display *_display;
};

#endif