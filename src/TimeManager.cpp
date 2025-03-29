#include "TimeManager.h"

TimeManager::TimeManager(NTPClient *client) : _client(client) {}

void TimeManager::begin()
{
    _client->begin();
}

void TimeManager::update()
{
    _client->update();
}

String TimeManager::getFormattedTime() const
{
    return _client->getFormattedTime();
}

String TimeManager::getDatePath() const
{
    return "/logs/" + String(_client->getEpochTime() / 86400);
}

String TimeManager::getFullTimestamp() const
{
    time_t rawTime = _client->getEpochTime();
    struct tm *ti = localtime(&rawTime);
    String date = String(ti->tm_mday) + "/" + String(ti->tm_mon + 1) + "/" + String(ti->tm_year + 1900);
    return date + " " + _client->getFormattedTime();
}