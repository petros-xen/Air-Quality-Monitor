# 🌍 Air Quality Monitor (ESP8266 + Firebase + Blynk)

A smart air quality monitoring system built with the ESP8266 that collects environmental data and displays it on:
- an OLED screen,
- Firebase Realtime Database,
- and a Blynk dashboard.

This project measures:
- 🌡 Temperature & 💧 Humidity (AHT20 sensor)
- 🗜 Atmospheric Pressure (BMP280)
- 💨 PM2.5 concentration (air particles)
- 💡 Ambient light (photoresistor)

## ✨ Features

- ✅ Real-time readings on OLED screen
- ✅ RGB LED to indicate air quality level
- ✅ Data logging to Firebase
- ✅ Blynk dashboard with live sensor updates
- ✅ Wi-Fi connectivity with NTP time sync
- ✅ Modular and maintainable code with custom libraries

## 📦 Hardware Used

- ESP8266 NodeMCU
- AHT20 (Temp & Humidity sensor)
- BMP280 (Pressure sensor)
- PMS7003 or GP2Y1010 (PM2.5 sensor)
- RGB LED
- Photoresistor (LDR)
- 0.96" I2C OLED display

## 🔧 Setup Instructions

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/air-quality-monitor.git
   cd air-quality-monitor
   ```

2. Install PlatformIO.

3. Rename `credentials.example.h` to `credentials.h` and add your Wi-Fi, Firebase, and Blynk credentials:

   ```cpp
   #define WIFI_SSID "your-ssid"
   #define WIFI_PASSWORD "your-password"

   #define FIREBASE_HOST "your-project.firebaseio.com"
   #define FIREBASE_DB_URL "https://your-project.firebaseio.com"
   #define FIREBASE_API_KEY "your-api-key"
   #define FIREBASE_EMAIL "your@email.com"
   #define FIREBASE_PASSWORD "your-password"
   ```

4. Pin Mapping Table.

| Component            | Function                 | GPIO Pin | NodeMCU Label |
|---------------------|--------------------------|----------|----------------|
| OLED Display        | SDA                      | GPIO12   | D6             |
| OLED Display        | SCL                      | GPIO14   | D5             |
| AHT20 + BMP280      | SDA                      | GPIO12   | D6             |
| AHT20 + BMP280      | SCL                      | GPIO14   | D5             |
| PM2.5 Sensor        | TX (sensor) → RX (ESP)   | GPIO13   | D7             |
| PM2.5 Sensor        | RX (sensor) → TX (ESP)   | GPIO15   | D8             |
| RGB LED             | RED                      | GPIO16   | D0             |
| RGB LED             | GREEN                    | GPIO0    | D3             |
| RGB LED             | BLUE                     | GPIO2    | D4             |
| Photoresistor       | Analog Output            | A0       | A0             |

---

5. Build and upload to your ESP8266 board via PlatformIO or Arduino IDE.

## 📊 Firebase Realtime Database Structure

```
logs/
  └── {date_id}/
      ├── {timestamp}/
      │   ├── temperature
      │   ├── humidity
      │   ├── pressure
      │   ├── pm25
      │   └── light
```

## 📱 Blynk Dashboard

- V0: Temperature
- V1: Humidity
- V2: PM2.5 Level

## 📁 Project Structure

```
├── include/                    # Header files
│   ├── AHT20_BMP280.h
│   ├── AirQualityManager.h
│   ├── credentials.example.h  # Template for secrets (do NOT commit credentials.h)
│   ├── credentials.h          # Your actual Wi-Fi + Firebase secrets (excluded from Git)
│   ├── FirebaseManager.h
│   ├── OLED_Display.h
│   ├── Photoresistor.h
│   ├── PM25_Sensor.h
│   ├── RGB_LED.h
│   ├── TimeManager.h
│   ├── WiFiManager.h
│   └── README                 # Local documentation / notes (optional)
│
├── src/                        # Source files
│   ├── AHT20_BMP280.cpp
│   ├── AirQualityManager.cpp
│   ├── credentials.cpp
│   ├── FirebaseManager.cpp
│   ├── main.cpp               # Main application logic
│   ├── OLED_Display.cpp
│   ├── Photoresistor.cpp
│   ├── PM25_Sensor.cpp
│   ├── RGB_LED.cpp
│   ├── TimeManager.cpp
│   └── WiFiManager.cpp
│
├── lib/                        # External libraries (optional / empty)
│
└── platformio.ini              # PlatformIO project configuration
```

## 🧠 Future Ideas

- 🧪 Add CO₂ or VOC sensor support
- ☁️ Use MQTT or HTTP to send data to a web dashboard
- 📈 Visualize data with charts

---

### License

This project is open-source and free to use under the MIT License.
