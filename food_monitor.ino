// 1. Blynk Credentials
#define BLYNK_TEMPLATE_ID "TMPL3XG-O4G0G"
#define BLYNK_TEMPLATE_NAME "Food Monitor"
#define BLYNK_AUTH_TOKEN "epcektjo4Q8GBkyUSK0iDRMwCysePjcZ"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Wokwi WiFi
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins (same as your wiring)
#define RED_LED   26
#define GREEN_LED 27
#define BUZZER    25

bool notificationSent = false;   // prevents repeat spam

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Food Status:");
  lcd.setCursor(0, 1);
  lcd.print("NOT SAFE");

  // LEDs & buzzer
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, HIGH);

  // Connect Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Update Blynk widgets
  Blynk.virtualWrite(V4, 1);  // Red LED ON
  Blynk.virtualWrite(V5, 0);  // Green LED OFF
  Blynk.virtualWrite(V0, 800); // Methane high
  Blynk.virtualWrite(V1, 4.2); // pH low
  Blynk.virtualWrite(V2, 85); // humidity
  Blynk.virtualWrite(V8, 900); // moisture
  // Send notification ONCE at startup
  if (!notificationSent) {
    Blynk.logEvent(
      "spoilage_alert",
      "? FOOD NOT SAFE!\nHigh Methane / Low pH detected."
    );
    notificationSent = true;
  }
}

void loop() {
  Blynk.run();
}