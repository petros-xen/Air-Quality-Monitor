#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Firebase.h>

class FirebaseManager
{
public:
    FirebaseManager(FirebaseConfig *cfg, FirebaseAuth *auth, FirebaseData *data);
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
};

#endif