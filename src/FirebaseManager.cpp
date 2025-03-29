#include "FirebaseManager.h"

FirebaseManager::FirebaseManager(FirebaseConfig *cfg, FirebaseAuth *auth, FirebaseData *data)
{
    config = cfg;
    this->auth = auth;
    firebaseData = data;
}

void FirebaseManager::begin()
{
    Firebase.begin(config, auth);
    Firebase.reconnectWiFi(true);
}

bool FirebaseManager::pushSensorData(const String &logPath,
                                     bool tempOk, float temp,
                                     bool humOk, float hum,
                                     bool pressureOk, float pressure,
                                     bool pmValid, float pm,
                                     int light)
{
    bool success = true;

    if (tempOk && !Firebase.setFloat(*firebaseData, logPath + "/temperature", roundf(temp * 100) / 100.0))
    {
        Serial.println("❌ Temp push failed: " + firebaseData->errorReason());
        success = false;
    }

    if (humOk && !Firebase.setFloat(*firebaseData, logPath + "/humidity", roundf(hum * 100) / 100.0))
    {
        Serial.println("❌ Humidity push failed: " + firebaseData->errorReason());
        success = false;
    }

    if (pressureOk && !Firebase.setFloat(*firebaseData, logPath + "/pressure", roundf(pressure * 100) / 100.0))
    {
        Serial.println("❌ Pressure push failed: " + firebaseData->errorReason());
        success = false;
    }

    if (pmValid && !Firebase.setFloat(*firebaseData, logPath + "/pm25", roundf(pm * 100) / 100.0))
    {
        Serial.println("❌ PM2.5 push failed: " + firebaseData->errorReason());
        success = false;
    }

    if (!Firebase.setInt(*firebaseData, logPath + "/light", light))
    {
        Serial.println("❌ Light push failed: " + firebaseData->errorReason());
        success = false;
    }

    return success;
}