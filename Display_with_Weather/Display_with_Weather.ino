// Libraries for I2C communication and the OLED display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Libraries for the DHT11 Temperature and Humidity sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>

// --- Pin Definitions ---
// For OLED Display (I2C)
#define OLED_SDA D2 // GPIO4
#define OLED_SCL D1 // GPIO5

// For DHT11 Sensor (from Experiment 3)
#define DHTPIN D4 // GPIO2
#define DHTTYPE DHT11

// --- OLED Display Setup ---
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- DHT Sensor Setup ---
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();

  // Initialize OLED display
  // The begin function requires the I2C address. 0x3C is the most common address for these displays.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show a startup message on the OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Weather Station");
  display.println("Starting up...");
  display.display();
  delay(2000);
}

void loop() {
  // Read Temperature and Humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Clear the display buffer
  display.clearDisplay();

  // Set text properties
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Check if sensor reading was successful
  if (isnan(h) || isnan(t)) {
    display.println("Failed to read");
    display.println("from DHT sensor!");
  } else {
    // Display Temperature
    display.print("Temp: ");
    display.print(t);
    display.println(" C");

    // Display Humidity on the next line
    display.print("Humidity: ");
    display.print(h);
    display.println(" %");
  }

  // Push data from the buffer to the screen
  display.display(); 
  
  // Wait 2 seconds before the next reading
  delay(2000);
}