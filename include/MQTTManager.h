#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <functional>

class MQTTManager
{
public:
    MQTTManager(Client &client);
    void begin(const char *server, uint16_t port, const char *user, const char *password);
    void setCallback(std::function<void(char *, uint8_t *, unsigned int)> callback);
    void publishSensorData(float temp, float hum, float pressure, float pm25);
    void reconnect(const char *clientId); // <- Make this public
    void publish(const char *topic, const char *payload);
    void loop();

private:
    PubSubClient mqttClient;
    const char *user;
    const char *password;
};

#endif