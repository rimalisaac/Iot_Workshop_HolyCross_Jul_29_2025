/****************************************************
   LDR Module Digital Output (D0) + ThingSpeak
   Board: ESP8266 (NodeMCU) / ESP32
   LDR module D0 -> Digital pin
****************************************************/

#include <WiFi.h>          // For ESP32. Use <ESP8266WiFi.h> if NodeMCU
#include "ThingSpeak.h"

const char* ssid = "YOUR_WIFI_SSID";     
const char* password = "YOUR_WIFI_PASS"; 

WiFiClient client;

// ThingSpeak settings
unsigned long myChannelNumber = YOUR_CHANNEL_ID;
const char* myWriteAPIKey = "YOUR_API_KEY";

// LDR digital pin
const int LDR_D0 = 14;  // Example: GPIO14 (D5 on NodeMCU, change as needed)

// ThingSpeak update timing
unsigned long lastUpdate = 0;
const long updateInterval = 20000;  // 15s minimum

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LDR_D0, INPUT);

  // Connect WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  // Read digital value (0 or 1)
  int ldrDigital = digitalRead(LDR_D0);

  // Print to Serial Monitor
  Serial.print("LDR Digital State: ");
  Serial.println(ldrDigital);

  // Send to ThingSpeak every 20s
  if (millis() - lastUpdate >= updateInterval) {
    int x = ThingSpeak.writeField(myChannelNumber, 1, ldrDigital, myWriteAPIKey);

    if (x == 200) {
      Serial.println("Data sent to ThingSpeak successfully.");
    } else {
      Serial.print("Error sending data. HTTP error code: ");
      Serial.println(x);
    }

    lastUpdate = millis();
  }

  delay(1000);
}
