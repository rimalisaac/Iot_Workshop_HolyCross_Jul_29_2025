#include <ESP8266WiFi.h>
#include <DHT.h>

// --- Configuration ---
// WiFi Network Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak API and Server
const char* server = "api.thingspeak.com";
String writeAPIKey = "YOUR_WRITE_API_KEY";

// DHT Sensor Setup (Assuming connection to pin D4 as in previous experiments)
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// WiFi client object
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read sensor values
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature as Celsius

  // Check if any readings failed and exit early to try again.
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Connect to the ThingSpeak server
  if (client.connect(server, 80)) {
    // Construct the data payload as an HTTP GET request
    String postStr = "GET /update?api_key=";
    postStr += writeAPIKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += " HTTP/1.1\r\n";
    postStr += "Host: api.thingspeak.com\r\n";
    postStr += "Connection: close\r\n\r\n";

    // Send the request to ThingSpeak
    client.print(postStr);
    
    Serial.print("Data sent to ThingSpeak: ");
    Serial.print("Temp=");
    Serial.print(t);
    Serial.print("C, Humidity=");
    Serial.print(h);
    Serial.println("%.");
  } else {
    Serial.println("Connection to ThingSpeak failed.");
  }
  
  client.stop();

  // ThingSpeak has a rate limit of about 15 seconds. 
  // A 20-second delay is safe.
  delay(20000); 
}