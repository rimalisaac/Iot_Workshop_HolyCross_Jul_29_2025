#include <TinyGPSPlus.h>
#include <HardwareSerial.h> // For ESP32 hardware serial

// Define the RX and TX pins for the GPS module
// ESP32 has multiple hardware serial ports. Serial2 is a good choice.
#define GPS_RX_PIN 16 // Connect GPS TX to ESP32 GPIO16 (RX2)
#define GPS_TX_PIN 17 // Connect GPS RX to ESP32 GPIO17 (TX2)

// Create a HardwareSerial object for the GPS module
HardwareSerial gpsSerial(2); // Use UART2 (0, 1, or 2 on ESP32)

// Create a TinyGPSPlus object
TinyGPSPlus gps;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor to be ready

  Serial.println("ESP32 with GY-NEO6MV2 GPS Module");
  Serial.println("---------------------------------");

  // Initialize the GPS serial communication
  // Default baud rate for NEO-6M is usually 9600
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  Serial.println("GPS module initialized. Waiting for data...");
  Serial.println("Make sure the GPS antenna has a clear view of the sky.");
}

void loop() {
  // While there is data available from the GPS module, feed it to TinyGPSPlus
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // A complete NMEA sentence has been processed
      displayInfo();
    }
  }

  // If no new data is coming in, check if a fix has been lost or needs update
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS data received or too few characters. Check wiring and antenna."));
    while(true); // Stop here if no data for a long time
  }
}

void displayInfo() {
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Altitude: "));
  if (gps.altitude.isValid()) {
    Serial.print(gps.altitude.meters());
    Serial.print(F("m"));
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Speed: "));
  if (gps.speed.isValid()) {
    Serial.print(gps.speed.kmph());
    Serial.print(F("km/h"));
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Satellites: "));
  if (gps.satellites.isValid()) {
    Serial.print(gps.satellites.value());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  HDOP: "));
  if (gps.hdop.isValid()) {
    Serial.print(gps.hdop.value() / 100.0); // HDOP is typically provided as an integer * 100
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date: "));
  if (gps.date.isValid()) {
    Serial.print(gps.date.year());
    Serial.print(F("-"));
    Serial.print(gps.date.month());
    Serial.print(F("-"));
    Serial.print(gps.date.day());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Time: "));
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}