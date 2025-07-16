#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // For HTTPS communication
#include <DHT.h>

// --- Configuration ---
// WiFi Network Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Google Script Details
const char* host = "script.google.com";
const int httpsPort = 443;
// Extract the Script ID from your Web App URL.
// URL: https://script.google.com/macros/s/YOUR_SCRIPT_ID/exec
String G_SCRIPT_ID = "YOUR_SCRIPT_ID"; 

// DHT Sensor Setup
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// HTTPS client object
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();

  // Set client to ignore fingerprint verification (less secure, but easier)
  client.setInsecure();

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  // Read sensor values
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Construct the URL for the GET request
  String url = "/macros/s/" + G_SCRIPT_ID + "/exec" + "?temp=" + String(t) + "&hum=" + String(h);

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // Connect to the Google Script server
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection to Google Scripts failed.");
    return;
  }

  // Send the HTTP GET request
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("Data sent to Google Sheet.");
  
  // Wait for the server to respond before closing the connection
  while (client.connected()) {
    if (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  client.stop();
  
  // Wait 30 seconds before sending the next reading
  delay(30000);
}