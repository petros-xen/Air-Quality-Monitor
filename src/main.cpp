#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#include "RGB_LED.h"
#include "credentials.h"
#include "OLED_Display.h"
#include "FirebaseManager.h"
#include "AirQualityManager.h"
#include "TimeManager.h"
#include "MQTTManager.h"
#include "OTAManager.h"

OLED_Display oledDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
AHT20_BMP280 sensor;
PM25_Sensor pm25(13, 15);
Photoresistor lightSensor(A0);
RGB_LED rgb(16, 0, 2);
AirQualityManager airQualityManager(&sensor, &pm25, &lightSensor);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);
TimeManager timeManager(&timeClient);

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;
FirebaseManager firebase(&config, &auth, &firebaseData, &timeManager);

WiFiClient espClient;
MQTTManager mqttManager(espClient);

OTAManager otaManager;

unsigned long lastReadTime = 0;
unsigned long lastPushTime = 0;
const unsigned long readInterval = 10000;
const unsigned long pushInterval = 300000;

void setup()
{
  Serial.begin(115200);
  Wire.begin(12, 14);
  sensor.begin(&Wire);
  delay(100);

  oledDisplay.begin();
  oledDisplay.showLoadingAnimation("Booting up...", 12, 120);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("📶 Connecting to WiFi");
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

  timeManager.begin();
  firebase.begin();
  otaManager.begin("AirQualityMonitor");
  mqttManager.begin(MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD);

  rgb.begin();
  pm25.begin();
  lightSensor.begin();
  analogWriteRange(255);
}

void loop()
{
  mqttManager.reconnect("AirQualityMonitor");
  mqttManager.loop();

  OTAManager::handle();

  unsigned long currentTime = millis();

  if (currentTime - lastReadTime >= readInterval)
  {
    lastReadTime = currentTime;
    timeManager.update();

    airQualityManager.update();
    AirQualityData data = airQualityManager.getData();

    if (data.pmValid)
      rgb.setColor(data.r, data.g, data.b);
    else
      rgb.setColor(255, 255, 255);

    rgb.setBrightnessFromLight(data.lightLevel);
    oledDisplay.showSensorData(data.temperature, data.tempValid, data.humidity, data.humidityValid, data.pressure, data.pressureValid, data.qualityLabel, data.pm25, timeManager.getFullTimestamp());

    mqttManager.publishSensorData(data.temperature, data.humidity, data.pressure, data.pm25);
  }

  if (currentTime - lastPushTime >= pushInterval)
  {
    lastPushTime = currentTime;
    String logPath = timeManager.getDatePath();
    AirQualityData data = airQualityManager.getData();

    firebase.pushSensorData(logPath,
                            data.tempValid, data.temperature,
                            data.humidityValid, data.humidity,
                            data.pressureValid, data.pressure,
                            data.pmValid, data.pm25,
                            data.lightLevel);
  }
}