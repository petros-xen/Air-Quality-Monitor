#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#pragma once
#include <ArduinoOTA.h>
#include "OLED_Display.h"

class OTAManager
{
public:
    static void begin(OLED_Display *display);
    static void handle();
};

#endif