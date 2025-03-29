// FirebaseManager.h
#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Firebase.h>
#include "TimeManager.h"

class FirebaseManager
{
public:
    // Update the constructor to include TimeManager
    FirebaseManager(FirebaseConfig *cfg, FirebaseAuth *auth, FirebaseData *data, TimeManager *timeMgr);
    void begin();

    bool pushSensorData(const String &logPath,
                        bool tempOk, float temp,
                        bool humOk, float hum,
                        bool pressureOk, float pressure,
                        bool pmValid, float pm,
                        int light);

private:
    FirebaseConfig *config;
    FirebaseAuth *auth;
    FirebaseData *firebaseData;
    TimeManager *timeManager; // ✅ Store pointer to TimeManager
};

#endif