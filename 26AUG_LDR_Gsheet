#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "YOUR_WIFI_SSID";     
const char* password = "YOUR_WIFI_PASS"; 

// Replace with your Google Script Web App URL
String GOOGLE_SCRIPT_URL = "https://script.google.com/macros/s/PASTE_YOUR_SCRIPT_URL/exec";

// LDR pin
const int LDR_D0 = D5;  

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
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

  // Ignore SSL certificate validation
  client.setInsecure();
}

void loop() {
  int ldrDigital = digitalRead(LDR_D0);
  Serial.print("LDR State: ");
  Serial.println(ldrDigital);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = GOOGLE_SCRIPT_URL + "?ldr=" + String(ldrDigital);

    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.begin(client, url);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Response: " + payload);
    } else {
      Serial.print("Error sending data. Code: ");
      Serial.println(httpCode);
    }

    http.end();
  }

  delay(20000); // log every 20s
}
