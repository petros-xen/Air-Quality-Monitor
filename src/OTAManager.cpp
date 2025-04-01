#include "OTAManager.h"

OLED_Display *OTAManager::_display = nullptr;

void OTAManager::begin(OLED_Display *display, const char *hostname)
{
    _display = display;

    ArduinoOTA.setHostname(hostname);

    ArduinoOTA.onStart([]()
                       {
                            Serial.println("🔄 OTA update started...");
                            if (_display)
                            {
                                _display->updateProgressBar("OTA update started...", 0);
                            } });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          {
                              int percent = (progress * 100) / total;
                              Serial.printf("📶 OTA Progress: %u%%\n", percent);

                              if (_display)
                              {
                                  _display->updateProgressBar("OTA Updating...", percent);
                              } });

    ArduinoOTA.onEnd([]()
                     {
                         Serial.println("✅ OTA update complete!");
                         if (_display)
                         {
                             _display->updateProgressBar("OTA complete!", 100);
                             delay(1500); // show the message briefly
                         } });

    ArduinoOTA.onError([](ota_error_t error)
                       {
                           Serial.printf("❌ OTA Error[%u]: ", error);
                           if (_display)
                               _display->updateProgressBar("OTA ERROR", 0); });

    ArduinoOTA.begin();
}

void OTAManager::handle()
{
    ArduinoOTA.handle();
}