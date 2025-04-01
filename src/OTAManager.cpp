#include "OTAManager.h"

void OTAManager::begin(const char *hostname)
{
    ArduinoOTA.setHostname(hostname);

    ArduinoOTA.onStart([]()
                       { Serial.println("🔄 OTA Update Start"); });

    ArduinoOTA.onEnd([]()
                     { Serial.println("\n✅ OTA Update Finished"); });

    ArduinoOTA.onError([](ota_error_t error)
                       {
        Serial.printf("❌ OTA Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

    ArduinoOTA.begin();
    Serial.println("🚀 OTA Ready");
}

void OTAManager::handle()
{
    ArduinoOTA.handle();
}