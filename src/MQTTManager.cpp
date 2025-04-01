#include "MQTTManager.h"

MQTTManager::MQTTManager(Client &client)
    : mqttClient(client)
{
}

void MQTTManager::begin(const char *server, uint16_t port, const char *user, const char *password)
{
    mqttClient.setServer(server, port);
    this->user = user;
    this->password = password;
}

void MQTTManager::setCallback(std::function<void(char *, uint8_t *, unsigned int)> callback)
{
    mqttClient.setCallback(callback);
}

void MQTTManager::reconnect(const char *clientId)
{
    while (!mqttClient.connected())
    {
        Serial.print("🔁 Connecting to MQTT... ");
        if (mqttClient.connect(clientId, user, password))
        {
            Serial.println("✅ connected!");
        }
        else
        {
            Serial.print("❌ failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" retrying in 5s...");
            delay(5000);
        }
    }
}

void MQTTManager::publishSensorData(float temp, float hum, float pressure, float pm25)
{
    String tempStr = String(temp, 2);
    String humStr = String(hum, 2);
    String pressStr = String(pressure, 2);
    String pmStr = String(pm25, 2);

    publish("air_quality/temperature", tempStr.c_str());
    publish("air_quality/humidity", humStr.c_str());
    publish("air_quality/pressure", pressStr.c_str());
    publish("air_quality/pm25", pmStr.c_str());

    Serial.println("📡 MQTT: Sensor data published.");
}

void MQTTManager::publish(const char *topic, const char *payload)
{
    if (mqttClient.connected())
    {
        mqttClient.publish(topic, payload);
    }
}

void MQTTManager::loop()
{
    mqttClient.loop();
}