// TimeManager.h
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <time.h>

class TimeManager
{
public:
    TimeManager(NTPClient *client); // <-- Match this
    void begin();
    void update();
    String getFormattedTime() const;
    String getDatePath() const;
    String getFullTimestamp() const;

private:
    NTPClient *_client;
};

#endif
