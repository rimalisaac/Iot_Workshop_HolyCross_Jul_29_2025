#include <ESP8266WiFi.h>

const char* ssid = "YOUR_WIFI_SSID";  
const char* password = "YOUR_WIFI_PASSWORD";  

WiFiServer server(80);

#define LED_PIN 2  // NodeMCU built-in LED = D4 (GPIO2)

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // OFF initially (active LOW)

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Note this IP for browser access

  server.begin();
}

void loop() {
  WiFiClient client = server.available();  
  if (!client) return;

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(LED_PIN, LOW);  // Turn LED ON
  }
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(LED_PIN, HIGH); // Turn LED OFF
  }

  // Build webpage
  String html = "<!DOCTYPE html><html><head><title>ESP8266 LED Control</title></head><body>";
  html += "<h1>ESP8266 LED Control</h1>";
  html += "<p><a href=\"/LED=ON\"><button>LED ON</button></a></p>";
  html += "<p><a href=\"/LED=OFF\"><button>LED OFF</button></a></p>";
  html += "</body></html>";

  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  client.print(html);
  delay(1);
}
