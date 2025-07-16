// Required Libraries for the DHT11 Sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Define the pin the DHT11 data pin is connected to (D4 on NodeMCU)
#define DHTPIN D4

// Define the type of DHT sensor we are using (DHT11)
#define DHTTYPE DHT11

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start serial communication to display readings on the computer
  Serial.begin(9600);
  Serial.println("Experiment 3: Digital Weather Station");

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait a couple of seconds between measurements.
  delay(2000);

  // Read Humidity from the sensor
  float h = dht.readHumidity();
  // Read temperature in Celsius from the sensor
  float t = dht.readTemperature();

  // Check if any readings failed and exit early to try again.
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
}