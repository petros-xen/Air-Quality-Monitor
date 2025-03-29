#include "FirebaseManager.h"
#include "credentials.h"

FirebaseManager::FirebaseManager(FirebaseConfig *cfg, FirebaseAuth *auth, FirebaseData *data, TimeManager *timeMgr)
{
    config = cfg;
    this->auth = auth;
    firebaseData = data;
    timeManager = timeMgr;
}

void FirebaseManager::begin()
{
    config->api_key = FIREBASE_API_KEY;
    config->database_url = FIREBASE_DB_URL;
    config->host = FIREBASE_HOST;

    auth->user.email = FIREBASE_EMAIL;
    auth->user.password = FIREBASE_PASSWORD;

    Firebase.begin(config, auth);
    Firebase.reconnectWiFi(true);

    Serial.println("🔐 Firebase.begin() called");

    unsigned long start = millis();
    while (!Firebase.ready() && millis() - start < 10000)
    {
        delay(500);
        Serial.print(".");
    }

    if (Firebase.ready())
    {
        Serial.println("\n✅ Firebase is ready!");
    }
    else
    {
        Serial.println("\n❌ Firebase is NOT ready.");
    }
}

String twoDigitString(int num)
{
    if (num < 10)
        return "0" + String(num);
    else
        return String(num);
}

bool FirebaseManager::pushSensorData(const String &logRoot,
                                     bool tempOk, float temp,
                                     bool humOk, float hum,
                                     bool pressureOk, float pressure,
                                     bool pmValid, float pm,
                                     int light)
{
    if (!Firebase.ready())
    {
        Serial.println("⚠️ Firebase not ready!");
        return false;
    }

    String timestamp = timeManager->getFormattedTime();
    time_t rawTime = timeManager->getEpochTime();
    struct tm *timeinfo = localtime(&rawTime);

    String datePath = logRoot + "/" +
                      twoDigitString(timeinfo->tm_mday) + "-" +
                      twoDigitString(timeinfo->tm_mon + 1) + "-" +
                      String(timeinfo->tm_year + 1900);
    String logPath = datePath + "/" + timestamp;

    Serial.println("📤 Uploading to: " + logPath);

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