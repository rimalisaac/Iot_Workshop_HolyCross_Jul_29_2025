// Required Library for the DHT11 Sensor
#include <DHT.h>

// --- Pin and Threshold Definitions ---
// For DHT11 Sensor (from previous experiments)
#define DHTPIN D4 // GPIO2
#define DHTTYPE DHT11

// For Piezo Buzzer
#define BUZZER_PIN D5 // GPIO14

// The temperature in Celsius to trigger the alert
#define TEMP_THRESHOLD 28.0

// --- Sensor Initialization ---
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("Temperature Alert System");

  // Set the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Read the temperature. Readings can take up to 2 seconds.
  float t = dht.readTemperature();

  // Check if the sensor reading failed
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return; // Exit the loop and try again
  }

  // Print the current temperature to the Serial Monitor
  Serial.print("Current Temperature: ");
  Serial.print(t);
  Serial.println(" °C");

  // Check if the temperature has exceeded the threshold
  if (t > TEMP_THRESHOLD) {
    Serial.println("ALERT! Temperature is too high!");
    // Sound the alarm (a 1000 Hz tone for half a second)
    tone(BUZZER_PIN, 1000); 
    delay(500);
    // Be silent for half a second to create a beeping pattern
    noTone(BUZZER_PIN);
    delay(500);
  } else {
    // If temperature is normal, make sure the buzzer is off
    noTone(BUZZER_PIN);
    Serial.println("Temperature is normal.");
  }
  
  // Wait a second before the next reading
  delay(1000);
}
