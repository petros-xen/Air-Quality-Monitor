#include "WiFiManager.h"
#include <Arduino.h>

WiFiManager::WiFiManager(const char *ssid, const char *password)
{
    _ssid = ssid;
    _password = password;
}

void WiFiManager::connect()
{
    Serial.print("📶 Connecting to WiFi");

    WiFi.begin(_ssid, _password);

    int wifiTimeout = 0;
    while (WiFi.status() != WL_CONNECTED && wifiTimeout < 20)
    {
        delay(500);
        Serial.print(".");
        wifiTimeout++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\n✅ WiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("\n❌ WiFi failed to connect.");
    }
}