#include "OTAManager.h"

static OLED_Display *oled = nullptr;
static int lastDisplayedProgress = -10;

void OTAManager::begin(OLED_Display *display)
{
    oled = display;

    ArduinoOTA.onStart([]()
                       {
        Serial.println("🔄 OTA update started...");
        if (oled) oled->showLoadingAnimation("OTA update started...", 14, 120); });

    ArduinoOTA.onEnd([]()
                     {
        Serial.println("✅ OTA update complete!");
        if (oled) oled->showLoadingAnimation("OTA complete!", 14, 120); });

    static int lastDisplayedProgress = -10;

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          {
    int percent = (progress * 100) / total;
    if (percent - lastDisplayedProgress >= 10) {  // Update every 10%
        lastDisplayedProgress = percent;
        String msg = "OTA " + String(percent) + "%";
        Serial.println(msg);
        if (oled) oled->showLoadingAnimation(msg, 14, 120);
    } });

    ArduinoOTA.onError([](ota_error_t error)
                       {
        Serial.printf("❌ OTA Error[%u]: ", error);
        if (oled) oled->showLoadingAnimation("OTA Error!", 14, 120); });

    ArduinoOTA.begin();
}

void OTAManager::handle()
{
    ArduinoOTA.handle();
}