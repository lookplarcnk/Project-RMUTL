#include <WiFiManager.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

// Telegram bot credentials
const char* botToken = "Your Token From Telegram";
const char* chatID = "Your Chat ID From Telegram"; // Get this by starting a chat with your bot and checking updates

// IR sensor pin
const int irSensorPin = 5;

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

void setup() {
  Serial.begin(115200);
  
  // IR Sensor
  pinMode(irSensorPin, INPUT);

  // WiFiManager: AutoConnect
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP32_Config_Portal"); // ชื่อพอร์ทัล WiFi
  
  Serial.println("Connected to WiFi!");

  // Allow insecure connections
  client.setInsecure();
}

void loop() {
  static bool lastState = LOW;
  bool currentState = digitalRead(irSensorPin);

  if (currentState != lastState) {
    lastState = currentState;
    if (currentState == HIGH) {
      String message = "มีพัสดุมาส่ง";
      bot.sendMessage(chatID, message, "");
      Serial.println(message);
    }
  }
  delay(100); // Reduce sensor jitter
}
