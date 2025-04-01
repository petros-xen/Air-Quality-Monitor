#include "OLED_Display.h"

OLED_Display::OLED_Display(uint8_t width, uint8_t height, TwoWire *wire, int8_t reset)
    : _display(width, height, wire, reset)
{
}

void OLED_Display::begin(uint8_t address)
{
    if (!_display.begin(SSD1306_SWITCHCAPVCC, address))
    {
        Serial.println(F("❌ OLED initialization failed"));
        while (true)
            ;
    }

    _display.clearDisplay();
    _display.display();
}

void OLED_Display::showBootMessage()
{
    _display.clearDisplay();
    _display.setTextSize(2);
    _display.setTextColor(WHITE);
    _display.setCursor(0, 20);
    _display.println("BOOTING...");
    _display.display();
}

void OLED_Display::showSensorData(float temp, bool tempOk,
                                  float hum, bool humOk,
                                  float pressure, bool pressureOk,
                                  const String &airQualityLabel,
                                  float pm25,
                                  const String &timestamp)
{
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(WHITE);
    _display.setCursor(0, 0);

    Serial.print("⏰ Date & Time: ");
    Serial.println(timestamp);

    _display.print("T AHT20: ");
    _display.println(tempOk ? String(temp) : "Error");

    _display.print("Humidity: ");
    _display.println(humOk ? String(hum) : "Error");

    _display.print("Pressure: ");
    _display.println(pressureOk ? String(pressure) : "Error");

    _display.print("Air: ");
    _display.println(airQualityLabel);

    _display.print("PM2.5: ");
    _display.println(pm25);

    _display.display();

    // 🖨️ Serial debug output
    Serial.println("---- Sensor Readings (OLED) ----");
    Serial.print("🌡 Temperature (AHT20): ");
    Serial.println(tempOk ? String(temp) : "Error");

    Serial.print("💧 Humidity (AHT20): ");
    Serial.println(humOk ? String(hum) : "Error");

    Serial.print("🗜 Pressure (BMP280): ");
    Serial.println(pressureOk ? String(pressure) : "Error");

    Serial.print("💨 PM2.5 Value: ");
    Serial.println(pm25);

    Serial.print("🌫 Air Quality: ");
    Serial.println(airQualityLabel);

    Serial.println("--------------------------------");
}

void OLED_Display::showLoadingAnimation(const String &message, int steps, int delayMs)
{
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(WHITE);
    _display.setCursor(0, 0);
    _display.println(message);
    _display.drawRect(0, 20, SCREEN_WIDTH, 10, WHITE);
    _display.display();

    int barWidth = SCREEN_WIDTH / steps;

    for (int i = 0; i <= steps; i++)
    {
        _display.fillRect(1, 21, i * barWidth - 2, 8, WHITE);
        _display.display();
        delay(delayMs);
    }
}

void OLED_Display::updateProgressBar(const String &message, int percentage)
{
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(WHITE);

    _display.setCursor(0, 0);
    _display.println(message);

    // Draw border for progress bar
    int barX = 0;
    int barY = 20;
    int barWidth = SCREEN_WIDTH;
    int barHeight = 10;

    _display.drawRect(barX, barY, barWidth, barHeight, WHITE);

    // Fill progress
    int fillWidth = (percentage * (barWidth - 2)) / 100;
    _display.fillRect(barX + 1, barY + 1, fillWidth, barHeight - 2, WHITE);

    // Show percentage text centered below the bar
    _display.setCursor(0, 35);
    _display.printf("Progress: %d%%", percentage);

    _display.display();
}